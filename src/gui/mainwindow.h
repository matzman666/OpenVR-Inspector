#pragma once
#include <QMainWindow>
#include "deviceitempage.h"
#include "ui_mainwindow.h"

class ItemViewModel;


class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget * parent = Q_NULLPTR);
	~MainWindow();

	void setItemModel(ItemViewModel*  model);

	void setPlainPage(const QString& text = QString(""));
	QTableWidget* setSimpleTablePage();
	DeviceItemPage* setDeviceItemPage();

	QAction* getQuitAction() { return ui.actionQuit; }
	void setQuitActionEnabled(bool value) { return ui.actionQuit->setEnabled(value); }
	QAction* getDisconnectAction() { return ui.actionDisconnect; }
	void setDisconnectActionEnabled(bool value) { return ui.actionDisconnect->setEnabled(value); }
	QAction* getSaveReportAction() { return ui.actionSaveReport; }
	void setSaveReportActionEnabled(bool value) { return ui.actionSaveReport->setEnabled(value); }
	QTextEdit* getEventLog() { return ui.eventLogText; }

	void expandTreeItem(const QModelIndex & index) { ui.treeView->expand(index); }

private:
	Ui::MainWindow ui;
	DeviceItemPage* deviceItemPage = nullptr;
	int deviceItemPageIndex = 0;
};
