#include "deviceitempage.h"
#include <QScrollBar>

DeviceItemPage::DeviceItemPage(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
}

DeviceItemPage::~DeviceItemPage() {
	
}

void DeviceItemPage::setIsConnected(const QString& value) {
	ui.isConnectedText->setText(value);
}

void DeviceItemPage::setIsValid(const QString& value) {
	ui.isValidText->setText(value);
}

void DeviceItemPage::setTrackingResult(const QString & value) {
	ui.trackingResultText->setText(value);
}

int DeviceItemPage::getSelectedTrackingUniverse() {
	return ui.trackingUniverseCombo->currentIndex();
}

void DeviceItemPage::setDevicePos(const QString& x, const QString& y, const QString& z) {
	ui.posXText->setText(x);
	ui.posYText->setText(y);
	ui.posZText->setText(z);
}

void DeviceItemPage::setDeviceRot(const QString& yaw, const QString& pitch, const QString& roll) {
	ui.rotYawText->setText(yaw);
	ui.rotPitchText->setText(pitch);
	ui.rotRollText->setText(roll);
}

void DeviceItemPage::setDeviceVel(const QString& x, const QString& y, const QString& z) {
	ui.velXText->setText(x);
	ui.velYText->setText(y);
	ui.velZText->setText(z);
}

void DeviceItemPage::setDeviceAngularVel(const QString& x, const QString& y, const QString& z) {
	ui.avelXText->setText(x);
	ui.avelYText->setText(y);
	ui.avelZText->setText(z);
}

void DeviceItemPage::setTouchedButtons(const QString & value) {
	ui.touchedButtonsText->setText(value);
}

void DeviceItemPage::setPressedButtons(const QString & value) {
	ui.pressedButtonsText->setText(value);
}

void DeviceItemPage::SetAxis0(const QString& x, const QString& y) {
	ui.axis0XText->setText(x);
	ui.axis0YText->setText(y);
}

void DeviceItemPage::SetAxis1(const QString& x, const QString& y) {
	ui.axis1XText->setText(x);
	ui.axis1YText->setText(y);
}

void DeviceItemPage::SetAxis2(const QString& x, const QString& y) {
	ui.axis2XText->setText(x);
	ui.axis2YText->setText(y);
}

void DeviceItemPage::SetAxis3(const QString& x, const QString& y) {
	ui.axis3XText->setText(x);
	ui.axis3YText->setText(y);
}

void DeviceItemPage::SetAxis4(const QString& x, const QString& y) {
	ui.axis4XText->setText(x);
	ui.axis4YText->setText(y);
}
