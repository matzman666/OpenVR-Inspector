#pragma once
#include <QWidget>
#include "ui_deviceitempage.h"

class DeviceItemPage : public QWidget {
	Q_OBJECT

public:
	DeviceItemPage(QWidget * parent = Q_NULLPTR);
	~DeviceItemPage();

	QTableWidget* getPropsTable() { return ui.propsTable; }
	
	void setIsConnected(const QString& value);
	void setIsValid(const QString& value);
	void setTrackingResult(const QString& value);

	int getSelectedTrackingUniverse();
	void setDevicePos(const QString& x, const QString& y, const QString& z);
	void setDeviceRot(const QString& yaw, const QString& pitch, const QString& roll);
	void setDeviceVel(const QString& x, const QString& y, const QString& z);
	void setDeviceAngularVel(const QString& x, const QString& y, const QString& z);

	void setTouchedButtons(const QString& value);
	void setPressedButtons(const QString& value);
	void SetAxis0(const QString& x, const QString& y);
	void SetAxis1(const QString& x, const QString& y);
	void SetAxis2(const QString& x, const QString& y);
	void SetAxis3(const QString& x, const QString& y);
	void SetAxis4(const QString& x, const QString& y);

private:
	Ui::DeviceItemPage ui;
};
