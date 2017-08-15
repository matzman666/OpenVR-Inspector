#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <openvr.h>
#include <iostream>
#include "logging.h"
#include "gui/mainwindow.h"
#include "model/itemviewmodel.h"

const char* logConfigFileName = "logging.conf";

const char* logConfigDefault =
"* GLOBAL:\n"
"	FORMAT = \"[%level] %datetime{%Y-%M-%d %H:%m:%s}: %msg\"\n"
"	ENABLED = true\n"
"	TO_FILE = false\n"
"	TO_STANDARD_OUTPUT = true\n"
"	MAX_LOG_FILE_SIZE = 2097152 ## 2MB\n"
"* TRACE:\n"
"	ENABLED = false\n"
"* DEBUG:\n"
"	ENABLED = false\n";

INITIALIZE_EASYLOGGINGPP

void myQtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
	QByteArray localMsg = msg.toLocal8Bit();
	switch (type) {
		case QtDebugMsg:
			LOG(DEBUG) << localMsg.constData() << " (" << context.file << ":" << context.line << ")";
			break;
		case QtInfoMsg:
			LOG(INFO) << localMsg.constData() << " (" << context.file << ":" << context.line << ")";
			break;
		case QtWarningMsg:
			LOG(WARNING) << localMsg.constData() << " (" << context.file << ":" << context.line << ")";
			break;
		case QtCriticalMsg:
			LOG(ERROR) << localMsg.constData() << " (" << context.file << ":" << context.line << ")";
			break;
		case QtFatalMsg:
			LOG(FATAL) << localMsg.constData() << " (" << context.file << ":" << context.line << ")";
			break;
	}
}


class MyQApplication : public QApplication {
public:
	using QApplication::QApplication;

	virtual bool notify(QObject * receiver, QEvent * event) override {
		try {
			return QApplication::notify(receiver, event);
		} catch (std::exception& e) {
			LOG(ERROR) << "Exception thrown from an event handler: " << e.what();
		}
		return false;
	}
};


int main(int argc, char *argv[]) {

	try {
		MyQApplication a(argc, argv);

		qInstallMessageHandler(myQtMessageHandler);

		// Configure logger
		QString logFilePath;
		START_EASYLOGGINGPP(argc, argv);
		el::Loggers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);
		auto logconfigfile = QFileInfo(logConfigFileName).absoluteFilePath();
		el::Configurations conf;
		if (QFile::exists(logconfigfile)) {
			conf.parseFromFile(logconfigfile.toStdString());
		} else {
			conf.parseFromText(logConfigDefault);
		}
		conf.setRemainingToDefault();
		el::Loggers::reconfigureAllLoggers(conf);
		LOG(INFO) << "Application started";
		LOG(INFO) << "Log Config: " << QDir::toNativeSeparators(logconfigfile).toStdString();
		if (!logFilePath.isEmpty()) {
			LOG(INFO) << "Log File: " << logFilePath;
		}

		// Init OpenVR
		vr::EVRInitError peError;
		vr::VR_Init(&peError, vr::VRApplication_Utility);
		if (peError != vr::VRInitError_None) {
			std::string msg("Could not start application: ");
			msg.append(vr::VR_GetVRInitErrorAsEnglishDescription(peError));
			QMessageBox::critical(nullptr, "Error", QString::fromStdString(msg));
			exit(-2);
		}

		MainWindow mainwindow;

		ItemViewModel itemViewModel(&mainwindow);
		mainwindow.setItemModel(&itemViewModel);
		QObject::connect(mainwindow.getQuitAction(), SIGNAL(triggered()), &a, SLOT(quit()));
		QObject::connect(mainwindow.getSaveReportAction(), SIGNAL(triggered()), &itemViewModel, SLOT(handleSaveReport()));
		QObject::connect(mainwindow.getDisconnectAction(), SIGNAL(triggered()), &itemViewModel, SLOT(shutdown()));
		itemViewModel.expandRootItems();

		mainwindow.show();
		auto retval = a.exec();

		itemViewModel.shutdown();
		return retval;

	} catch (const std::exception& e) {
		LOG(FATAL) << e.what();
		return -1;
	}
	return 0;
}
