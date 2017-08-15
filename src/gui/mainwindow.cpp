#include "mainwindow.h"
#include "../logging.h"
#include "../model/itemviewmodel.h"
#include <QModelIndex>


MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent) {
	ui.setupUi(this);
	deviceItemPage = new DeviceItemPage();
	deviceItemPageIndex = ui.stackedWidget->addWidget(deviceItemPage);
	//ui.eventLogText->document()->setMaximumBlockCount(2000);
}

MainWindow::~MainWindow() {
	
}

void MainWindow::setItemModel(ItemViewModel * model) {
	ui.treeView->setModel(model);
	connect(ui.treeView->selectionModel(), &QItemSelectionModel::currentChanged, model, &ItemViewModel::currentItemChanged);
}

void MainWindow::setPlainPage(const QString& text) {
	ui.stackedWidget->setCurrentIndex(0);
	ui.plainPageText->setText(text);
}

QTableWidget * MainWindow::setSimpleTablePage() {
	ui.stackedWidget->setCurrentIndex(1);
	return ui.simpleTableWidget;
}

DeviceItemPage * MainWindow::setDeviceItemPage() {
	ui.stackedWidget->setCurrentIndex(deviceItemPageIndex);
	return deviceItemPage;
}

