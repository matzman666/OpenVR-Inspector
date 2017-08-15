#include "itemviewmodel.h"
#include "../logging.h"
#include "../gui/mainwindow.h"
#include <QDateTime>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>




std::map<int, const char*> ItemViewModel::applicationPropertyNames = {
	{ 0, "Name" },
	{ 11, "LaunchType" },
	{ 12, "WorkingDirectory" },
	{ 13, "BinaryPath" },
	{ 14, "Arguments" },
	{ 15, "URL" },
	{ 50, "Description" },
	{ 51, "NewsURL" },
	{ 52, "ImagePath" },
	{ 53, "Source" },
	{ 60, "IsDashboardOverlay" },
	{ 61, "IsTemplate" },
	{ 62, "IsInstanced" },
	{ 63, "IsInternal" },
	{ 64, "WantsCompositorPauseInStandby" },
	{ 70, "LastLaunchTime" },
};


std::map<int, const char*> ItemViewModel::devicePropertyNames = {
	{ 1000, "TrackingSystemName"},
	{ 1001, "ModelNumber" },
	{ 1002, "SerialNumber" },
	{ 1003, "RenderModelName" },
	{ 1004, "WillDriftInYaw" },
	{ 1005, "ManufacturerName" },
	{ 1006, "TrackingFirmwareVersion" },
	{ 1007, "HardwareRevision" },
	{ 1008, "AllWirelessDongleDescription" },
	{ 1009, "ConnectedWirelessDongle" },
	{ 1010, "DeviceIsWireless" },
	{ 1011, "DeviceIsCharging" },
	{ 1012, "DeviceBatteryPercentage" },
	{ 1013, "StatusDisplayTransform" },
	{ 1014, "FirmwareUpdateAvailable" },
	{ 1015, "FirmwareManualUpdate" },
	{ 1016, "FirmwareManualUpdateURL" },
	{ 1017, "HardwareRevision" },
	{ 1018, "FirmwareVersion" },
	{ 1019, "FPGAVersion" },
	{ 1020, "VRCVersion" },
	{ 1021, "RadioVersion" },
	{ 1022, "DongleVersion" },
	{ 1023, "BlockServerShutdown" },
	{ 1024, "CanUnifyCoordinateSystemWithHmd" },
	{ 1025, "ContainsProximitySensor" },
	{ 1026, "DeviceProvidesBatteryStatus" },
	{ 1027, "DeviceCanPowerOff" },
	{ 1028, "FirmwareProgrammingTarget" },
	{ 1029, "DeviceClass" },
	{ 1030, "HasCamera" },
	{ 1031, "DriverVersion" },
	{ 1032, "FirmwareForceUpdateRequired" },
	{ 1033, "ViveSystemButtonFixRequired" },
	{ 1034, "ParentDriver" },
	{ 1035, "ResourceRoot" },
	{ 2000, "ReportsTimeSinceVSync" },
	{ 2001, "SecondsFromVsyncToPhotons" },
	{ 2002, "DisplayFrequency" },
	{ 2003, "UserIpdMeters" },
	{ 2004, "CurrentUniverseId" },
	{ 2005, "PreviousUniverseId" },
	{ 2006, "DisplayFirmwareVersion" },
	{ 2007, "IsOnDesktop" },
	{ 2008, "DisplayMCType" },
	{ 2009, "DisplayMCOffset" },
	{ 2010, "DisplayMCScale" },
	{ 2011, "EdidVendorID" },
	{ 2012, "DisplayMCImageLeft" },
	{ 2013, "DisplayMCImageRight" },
	{ 2014, "DisplayGCBlackClamp" },
	{ 2015, "EdidProductID" },
	{ 2016, "CameraToHeadTransform" },
	{ 2017, "DisplayGCType" },
	{ 2018, "DisplayGCOffset" },
	{ 2019, "DisplayGCScale" },
	{ 2020, "DisplayGCPrescale" },
	{ 2021, "DisplayGCImage" },
	{ 2022, "LensCenterLeftU" },
	{ 2023, "LensCenterLeftV" },
	{ 2024, "LensCenterRightU" },
	{ 2025, "LensCenterRightV" },
	{ 2026, "UserHeadToEyeDepthMeters" },
	{ 2027, "CameraFirmwareVersion" },
	{ 2028, "CameraFirmwareDescription" },
	{ 2029, "DisplayFPGAVersion" },
	{ 2030, "DisplayBootloaderVersion" },
	{ 2031, "DisplayHardwareVersion" },
	{ 2032, "AudioFirmwareVersion" },
	{ 2033, "CameraCompatibilityMode" },
	{ 2034, "ScreenshotHorizontalFieldOfViewDegrees" },
	{ 2035, "ScreenshotVerticalFieldOfViewDegrees" },
	{ 2036, "DisplaySuppressed" },
	{ 2037, "DisplayAllowNightMode" },
	{ 2038, "DisplayMCImageWidth" },
	{ 2039, "DisplayMCImageHeight" },
	{ 2040, "DisplayMCImageNumChannels" },
	{ 2041, "DisplayMCImageData" },
	{ 2042, "SecondsFromPhotonsToVblank" },
	{ 2043, "DriverDirectModeSendsVsyncEvents" },
	{ 2044, "DisplayDebugMode" },
	{ 2045, "GraphicsAdapterLuid" },
	{ 2048, "DriverProvidedChaperonePath" },
	{ 3000, "AttachedDeviceId" },
	{ 3001, "SupportedButtons" },
	{ 3002, "Axis0Type" },
	{ 3003, "Axis1Type" },
	{ 3004, "Axis2Type" },
	{ 3005, "Axis3Type" },
	{ 3006, "Axis4Type" },
	{ 3007, "ControllerRoleHint" },
	{ 4000, "FieldOfViewLeftDegrees" },
	{ 4001, "FieldOfViewRightDegrees" },
	{ 4002, "FieldOfViewTopDegrees" },
	{ 4003, "FieldOfViewBottomDegrees" },
	{ 4004, "TrackingRangeMinimumMeters" },
	{ 4005, "TrackingRangeMaximumMeters" },
	{ 4006, "ModeLabel" },
	{ 5000, "IconPathName" },
	{ 5001, "NamedIconPathDeviceOff" },
	{ 5002, "NamedIconPathDeviceSearching" },
	{ 5003, "NamedIconPathDeviceSearchingAlert" },
	{ 5004, "NamedIconPathDeviceReady" },
	{ 5005, "NamedIconPathDeviceReadyAlert" },
	{ 5006, "NamedIconPathDeviceNotReady" },
	{ 5007, "NamedIconPathDeviceStandby" },
	{ 5008, "NamedIconPathDeviceAlertLow" },
	{ 5100, "DisplayHiddenArea_Binary_Start" },
	{ 5150, "DisplayHiddenArea_Binary_End" },
	{ 6000, "UserConfigPath" },
	{ 6001, "InstallPath" },
	{ 6002, "HasDisplayComponent" },
	{ 6003, "HasControllerComponent" },
	{ 6004, "HasCameraComponent" },
	{ 6005, "HasDriverDirectModeComponent" },
	{ 6006, "HasVirtualDisplayComponent" },
};


std::map<int, const char*> ItemViewModel::controllerAxisTypeNames = {
	{ 0, "None" },
	{ 1, "TrackPad" },
	{ 2, "Joystick" },
	{ 3, "Trigger" },
};


std::map<int, const char*> ItemViewModel::controllerRoleNames = {
	{ 0, "Invalid" },
	{ 1, "LeftHand" },
	{ 2, "RightHand" },
};


std::map<int, const char*> ItemViewModel::deviceClassNames = {
	{ 0, "Invalid" },
	{ 1, "HMD" },
	{ 2, "Controller" },
	{ 3, "GenericTracker" },
	{ 4, "TrackingReference" },
	{ 5, "DisplayRedirect" },
};


std::map<int, const char*> ItemViewModel::buttonNames = {
	{ 0, "System"},
	{ 1, "ApplicationMenu" },
	{ 2, "Grip" },
	{ 3, "DPad_Left" },
	{ 4, "DPad_Up" },
	{ 5, "DPad_Right" },
	{ 6, "DPad_Down" },
	{ 7, "Button_A" },
	{ 31, "ProximitySensor" },
	{ 32, "Axis0" },
	{ 33, "Axis1" },
	{ 34, "Axis2" },
	{ 35, "Axis3" },
	{ 36, "Axis4" },
};


std::map<int, const char*> ItemViewModel::trackingResultNames = {
	{ 1, "Uninitialized" },
	{ 100, "Calibrating_InProgress" },
	{ 101, "Calibrating_OutOfRange" },
	{ 200, "Running_OK" },
	{ 201, "Running_OutOfRange" },
};



ItemViewModel::ItemViewModel(MainWindow* mainWindow, QObject * parent) : QAbstractItemModel(parent), mainWindow(mainWindow) {
	deviceRootItem = std::shared_ptr<AbstractItem>(new TreeNode("Tracked Devices"));
	driversRootItem = std::shared_ptr<AbstractItem>(new TreeNode("Drivers"));
	applicationsRootItem = std::shared_ptr<AbstractItem>(new TreeNode("Applications"));
	rootItem.addChild(deviceRootItem);
	rootItem.addChild(applicationsRootItem);
	rootItem.addChild(driversRootItem);
	reloadTrackedDevices();
	reloadDrivers();
	reloadApplications();
	QObject::connect(&eventTimer, SIGNAL(timeout()), this, SLOT(onTimerEvent()));
	eventTimer.start(100);
}

ItemViewModel::~ItemViewModel() {
	
}


QModelIndex ItemViewModel::parent(const QModelIndex & index) const {
	QModelIndex retval;
	if (!index.isValid()) {
		return QModelIndex();
	} else {
		auto item = static_cast<AbstractItem*>(index.internalPointer());
		if (item != nullptr && item->parent != &rootItem) {
			return createIndex(item->parent->row, 0, item->parent);
		}
	}
	//LOG(INFO) << "TreeViewModel::parent(" << index.internalPointer() << ") = " << retval.internalPointer();
	return retval;
}

int ItemViewModel::rowCount(const QModelIndex & parent) const {
	int retval = 0;
	if (!parent.isValid()) {
		retval = (int)rootItem.children.size();
	} else {
		auto parentItem = static_cast<AbstractItem*>(parent.internalPointer());
		if (parentItem != nullptr) {
			retval = (int)parentItem->children.size();
		}
	}
	//LOG(INFO) << "TreeViewModel::rowCount(" << parent.internalPointer() << ") = " << retval;
	return retval;
}

int ItemViewModel::columnCount(const QModelIndex& /*parent*/) const {
	//LOG(INFO) << "TreeViewModel::columnCount(" << parent.internalPointer() << ")";
	return 1;
}

QModelIndex ItemViewModel::index(int row, int column, const QModelIndex & parent) const {
	const AbstractItem* parentItem;
	QModelIndex retval;
	if (!parent.isValid()) {
		parentItem = &rootItem;
	} else {
		parentItem = static_cast<AbstractItem*>(parent.internalPointer());
	}
	if (row < parentItem->children.size()) {
		auto childItem = parentItem->children[row].get();
		if (childItem) {
			retval = createIndex(row, column, childItem);
		}
	}
	//LOG(INFO) << "TreeViewModel::index(" << row << ", " << column << ", " << parent.internalPointer() << ") = " << retval.internalPointer();
	return retval;
}


QVariant ItemViewModel::data(const QModelIndex & index, int role) const {
	QVariant retval;
	if (index.isValid()) {
		auto indexItem = static_cast<AbstractItem*>(index.internalPointer());
		if (indexItem) {
			retval = indexItem->data(index, role);
		}
	}
	//LOG(INFO) << "TreeViewModel::data(" << index.internalPointer() << ", " << role << ") = " << retval.toString();
	return retval;
}


void ItemViewModel::expandRootItems() {
	mainWindow->expandTreeItem(createIndex(deviceRootItem->row, 0, deviceRootItem.get()));
	mainWindow->expandTreeItem(createIndex(driversRootItem->row, 0, driversRootItem.get()));
	mainWindow->expandTreeItem(createIndex(applicationsRootItem->row, 0, applicationsRootItem.get()));
}

void ItemViewModel::reloadTrackedDevices() {
	std::lock_guard<std::recursive_mutex> lock(mutex);
	if (openvrConnected) {
		deviceRootItem->children.clear();
		for (uint32_t i = 0; i < vr::k_unMaxTrackedDeviceCount; i++) {
			auto deviceClass = vr::VRSystem()->GetTrackedDeviceClass(i);
			if (deviceClass != vr::TrackedDeviceClass_Invalid) {
				auto deviceItem = std::make_shared<TrackedDeviceItem>();
				deviceItem->openvrId = i;
				deviceItem->deviceClass = deviceClass;
				auto classIt = deviceClassNames.find(deviceClass);
				if (classIt != deviceClassNames.end()) {
					deviceItem->deviceClassName = std::string(classIt->second);
				} else {
					deviceItem->deviceClassName = "Unknown";
				}
				char serialBuffer[vr::k_unMaxPropertyStringSize];
				vr::ETrackedPropertyError pError;
				vr::VRSystem()->GetStringTrackedDeviceProperty(deviceItem->openvrId, vr::Prop_SerialNumber_String, serialBuffer, vr::k_unMaxPropertyStringSize, &pError);
				if (pError == vr::TrackedProp_Success) {
					deviceItem->deviceSerial = serialBuffer;
				} else {
					LOG(ERROR) << "Could not get serial of device " << deviceItem->openvrId << ": " << vr::VRSystem()->GetPropErrorNameFromEnum(pError);
					deviceItem->deviceSerial = "<ERROR>";
				}
				deviceItem->displayName = std::to_string(deviceItem->openvrId) + ": " + deviceItem->deviceClassName + " (" + deviceItem->deviceSerial + ")";
				deviceRootItem->addChild(deviceItem);
			}
		}
	}
}

void ItemViewModel::reloadDrivers() {
	std::lock_guard<std::recursive_mutex> lock(mutex);
	if (openvrConnected) {
		driversRootItem->children.clear();
		auto driverCount = vr::VRDriverManager()->GetDriverCount();
		for (uint32_t i = 0; i < driverCount; i++) {
			auto driverItem = std::make_shared<DriverItem>();
			driverItem->index = i;
			char nameBuffer[vr::k_unMaxApplicationKeyLength];
			auto retval = vr::VRDriverManager()->GetDriverName(i, nameBuffer, vr::k_unMaxApplicationKeyLength);
			if (retval > 0) {
				driverItem->name = nameBuffer;
			} else {
				driverItem->name = "<ERROR>";
			}
			driversRootItem->addChild(driverItem);
		}
	}
}

void ItemViewModel::reloadApplications() {
	std::lock_guard<std::recursive_mutex> lock(mutex);
	if (openvrConnected) {
		applicationsRootItem->children.clear();
		auto appCount = vr::VRApplications()->GetApplicationCount();
		for (uint32_t i = 0; i < appCount; i++) {
			auto appItem = std::make_shared<ApplicationItem>();
			appItem->index = i;
			char keyBuffer[vr::k_unMaxApplicationKeyLength];
			vr::EVRApplicationError aError = vr::VRApplications()->GetApplicationKeyByIndex(i, keyBuffer, vr::k_unMaxApplicationKeyLength);
			if (aError == vr::VRApplicationError_None) {
				appItem->key = keyBuffer;
			} else{
				LOG(ERROR) << "Could not get key of app " << i << ": " << vr::VRApplications()->GetApplicationsErrorNameFromEnum(aError);
				appItem->key = "<ERROR>";
			}
			applicationsRootItem->addChild(appItem);
		}
	}
}

void ItemViewModel::shutdown() {
	std::lock_guard<std::recursive_mutex> lock(mutex);
	if (openvrConnected) {
		openvrConnected = false;
		eventTimer.stop();
		vr::VR_Shutdown();
		mainWindow->setDisconnectActionEnabled(false);
		mainWindow->setSaveReportActionEnabled(false);
		mainWindow->getEventLog()->append(QDateTime::currentDateTime().toString("dd.MM.yy-hh:mm:ss.zzz: ").append("Disconnected from OpenVR runtime.\n"));
	}
}

void ItemViewModel::onTimerEvent() {
	std::lock_guard<std::recursive_mutex> lock(mutex);
	if (openvrConnected) {
		// handle events
		vr::VREvent_t vrEvent;
		while (vr::VRSystem()->PollNextEvent(&vrEvent, sizeof(vr::VREvent_t))) {
		
			//LOG(INFO) << "VREvent: " << vr::VRSystem()->GetEventTypeNameFromEnum((vr::EVREventType)vrEvent.eventType);
			auto timestamp = QDateTime::currentDateTime();
			QString logTxt = timestamp.toString("dd.MM.yy-hh:mm:ss.zzz: ");
			logTxt.append("Reveiced event \"").append(vr::VRSystem()->GetEventTypeNameFromEnum((vr::EVREventType)vrEvent.eventType)).append("\": ");

			switch (vrEvent.eventType) {

			case vr::VREvent_ButtonPress:
			case vr::VREvent_ButtonUnpress:
			case vr::VREvent_ButtonTouch:
			case vr::VREvent_ButtonUntouch: {
				logTxt.append("controller.button = ").append(QString::number(vrEvent.data.controller.button)).append(" (")
					.append(getButtonName(vrEvent.data.controller.button)).append(")");
			} break;

			case vr::VREvent_FocusEnter:
			case vr::VREvent_FocusLeave:
			case vr::VREvent_OverlayFocusChanged: {
				logTxt.append("overlay.handle = ").append(QString::number(vrEvent.data.overlay.overlayHandle)).append(" (")
					.append(getButtonName(vrEvent.data.controller.button)).append(")");
			} break;

			case vr::VREvent_MouseMove:
			case vr::VREvent_MouseButtonDown:
			case vr::VREvent_MouseButtonUp:
			case vr::VREvent_Scroll:
			case vr::VREvent_TouchPadMove: {
				logTxt.append("mouse = { button = ").append(QString::number(vrEvent.data.mouse.button)).append(", ")
					.append("x = ").append(QString::number(vrEvent.data.mouse.x)).append(", ")
					.append("y = ").append(QString::number(vrEvent.data.mouse.y)).append(" }");
			} break;

			case vr::VREvent_InputFocusCaptured:
			case vr::VREvent_InputFocusReleased:
			case vr::VREvent_SceneFocusLost:
			case vr::VREvent_SceneFocusGained:
			case vr::VREvent_SceneApplicationChanged:
			case vr::VREvent_SceneFocusChanged:
			case vr::VREvent_InputFocusChanged:
			case vr::VREvent_Quit:
			case vr::VREvent_ProcessQuit:
			case vr::VREvent_QuitAborted_UserPrompt:
			case vr::VREvent_QuitAcknowledged:
			case vr::VREvent_ProcessConnected:
			case vr::VREvent_ProcessDisconnected:
			case vr::VREvent_SceneApplicationSecondaryRenderingStarted: {
				logTxt.append("process = { pid = ").append(QString::number(vrEvent.data.process.pid)).append(", ")
					.append("oldPid = ").append(QString::number(vrEvent.data.process.oldPid)).append(", ")
					.append("forced = ").append(QString::number(vrEvent.data.process.bForced)).append(" }");
				if (vrEvent.eventType == vr::VREvent_Quit) {
					mainWindow->getEventLog()->append(logTxt);
					shutdown();
					return;
				}
			} break;

			case vr::VREvent_ChaperoneDataHasChanged:
			case vr::VREvent_ChaperoneUniverseHasChanged:
			case vr::VREvent_ChaperoneTempDataHasChanged:
			case vr::VREvent_SeatedZeroPoseReset: {
				logTxt.append("chaperone = { currentUniverse = ").append(QString::number(vrEvent.data.chaperone.m_nCurrentUniverse)).append(", ")
					.append("previousUniverse = ").append(QString::number(vrEvent.data.chaperone.m_nPreviousUniverse)).append(" }");
			} break;

			case vr::VREvent_TrackedDeviceActivated: {
				bool devicesAdded = false;
				for (uint32_t i = (uint32_t)deviceRootItem->children.size(); i < vr::k_unMaxTrackedDeviceCount; i++) {
					auto deviceClass = vr::VRSystem()->GetTrackedDeviceClass(i);
					if (deviceClass != vr::TrackedDeviceClass_Invalid) {
						auto deviceItem = std::make_shared<TrackedDeviceItem>();
						deviceItem->openvrId = i;
						deviceItem->deviceClass = deviceClass;
						auto classIt = deviceClassNames.find(deviceClass);
						if (classIt != deviceClassNames.end()) {
							deviceItem->deviceClassName = std::string(classIt->second);
						} else {
							deviceItem->deviceClassName = "Unknown";
						}
						char serialBuffer[vr::k_unMaxPropertyStringSize];
						vr::ETrackedPropertyError pError;
						vr::VRSystem()->GetStringTrackedDeviceProperty(deviceItem->openvrId, vr::Prop_SerialNumber_String, serialBuffer, vr::k_unMaxPropertyStringSize, &pError);
						if (pError == vr::TrackedProp_Success) {
							deviceItem->deviceSerial = serialBuffer;
						} else {
							LOG(ERROR) << "Could not get serial of device " << deviceItem->openvrId << ": " << vr::VRSystem()->GetPropErrorNameFromEnum(pError);
							deviceItem->deviceSerial = "<ERROR>";
						}
						deviceItem->displayName = std::to_string(deviceItem->openvrId) + ": " + deviceItem->deviceClassName + " (" + deviceItem->deviceSerial + ")";
						if (!devicesAdded) {
							devicesAdded = true;
							beginResetModel();
						}
						beginInsertRows(createIndex(deviceRootItem->row, 0, &deviceRootItem), (int)deviceRootItem->children.size(), (int)deviceRootItem->children.size());
						deviceRootItem->addChild(deviceItem);
						endInsertRows();
					}
				}
				if (devicesAdded) {
					endResetModel();
					expandRootItems();
				}
			}
			break;

			case vr::VREvent_ApplicationListUpdated:
				mainWindow->setPlainPage();
				beginResetModel();
				reloadApplications();
				endResetModel();
				expandRootItems();
			case vr::VREvent_ApplicationTransitionStarted:
			case vr::VREvent_ApplicationTransitionAborted:
			case vr::VREvent_ApplicationTransitionNewAppStarted:
			case vr::VREvent_ApplicationMimeTypeLoad:
			case vr::VREvent_ApplicationTransitionNewAppLaunchComplete: {
				logTxt.append("applicationLaunch = { pid = ").append(QString::number(vrEvent.data.applicationLaunch.pid)).append(", ")
					.append("ArgsHandle = ").append(QString::number(vrEvent.data.applicationLaunch.unArgsHandle)).append(" }");
			} break;

			case vr::VREvent_PropertyChanged: {
				auto propName = getDevicePropertyName(vrEvent.data.property.prop);
				if (!propName.isEmpty()) {
					propName = QString(" (").append(propName).append(")");
				}
				logTxt.append("property = { container = ").append(QString::number(vrEvent.data.property.container)).append(", ")
					.append("prop = ").append(QString::number(vrEvent.data.property.prop)).append(propName).append(" }");
			} break;

			default:
				break;
			}

			mainWindow->getEventLog()->append(logTxt);
		}

		// Handle active item
		if (activeItem) {
			if (activeItem->itemType == ItemType::TrackedDevice) {
				auto deviceItem = static_cast<TrackedDeviceItem*>(activeItem);
				updateTrackedDevicePage(deviceItem);
			}
		}
	}
}



void ItemViewModel::currentItemChanged(const QModelIndex& current, const QModelIndex&) {
	if (current.isValid()) {
		auto item = static_cast<AbstractItem*>(current.internalPointer());
		if (item) {
			if (item->itemType == ItemType::Application) {
				ApplicationItem* appItem = static_cast<ApplicationItem*>(item);
				handleApplicationItemSelected(appItem);
			} else if (item->itemType == ItemType::TrackedDevice) {
				TrackedDeviceItem* deviceItem = static_cast<TrackedDeviceItem*>(item);
				handleTrackedDeviceItemSelected(deviceItem);
			} else if (item->itemType == ItemType::Driver) {
				mainWindow->setPlainPage("No information available.");
			} else if (item->itemType == ItemType::TreeNode) {
				QString text = QString::number(item->children.size()).append(" children");
				mainWindow->setPlainPage(text);
			} else {
				mainWindow->setPlainPage();
			}
			activeItem = item;
		} else {
			activeItem = nullptr;
		}
	}
}


void ItemViewModel::handleApplicationItemSelected(ApplicationItem* appItem) {
	std::lock_guard<std::recursive_mutex> lock(mutex);
	if (openvrConnected) {
		auto table = mainWindow->setSimpleTablePage();
		// Setup table
		table->clear();
		table->setColumnCount(3);
		table->horizontalHeader()->setDefaultSectionSize(600);
		table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
		table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);
		table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
		table->setHorizontalHeaderItem(0, new QTableWidgetItem("Property Name"));
		table->setHorizontalHeaderItem(1, new QTableWidgetItem("Property Value"));
		table->setHorizontalHeaderItem(2, new QTableWidgetItem("Property Type"));
		table->horizontalHeader()->setVisible(true);
		table->setStyleSheet("QHeaderView::section {background-color:lightgray}");
		QFont boldFont;
		boldFont.setWeight(QFont::Bold);
		// Iterate over application properties
		int tableRow = 0;
		for (int i = 0; i < 255; i++) {
			QString nameString;
			QString valueString;
			QString typeString;
			if (getApplicationProperty(appItem->key.c_str(), i, nameString, valueString, typeString)) {
				if (nameString.isEmpty()) {
					nameString = QString::number(i);
				} else {
					nameString = QString::number(i).append(" (").append(nameString).append(")");
				}
				QTableWidgetItem* nameItem = new QTableWidgetItem(nameString);
				nameItem->setFont(boldFont);
				QTableWidgetItem* valueItem = new QTableWidgetItem(valueString);
				QTableWidgetItem* typeItem = new QTableWidgetItem(typeString);
				table->setRowCount(tableRow + 1);
				table->setItem(tableRow, 0, nameItem);
				table->setItem(tableRow, 1, valueItem);
				table->setItem(tableRow, 2, typeItem);
				tableRow++;
			}
		}
	} else {
		mainWindow->setPlainPage("No Connection to OpenVR Runtime.");
	}
}


void ItemViewModel::handleTrackedDeviceItemSelected(TrackedDeviceItem * deviceItem) {
	std::lock_guard<std::recursive_mutex> lock(mutex);
	if (openvrConnected) {
		deviceItemPage = mainWindow->setDeviceItemPage();
	
		updateTrackedDevicePage(deviceItem);

		auto table = deviceItemPage->getPropsTable();
		// Setup table
		table->clear();
		table->setColumnCount(3);
		table->horizontalHeader()->setDefaultSectionSize(600);
		table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
		table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);
		table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
		table->setHorizontalHeaderItem(0, new QTableWidgetItem("Property Name"));
		table->setHorizontalHeaderItem(1, new QTableWidgetItem("Property Value"));
		table->setHorizontalHeaderItem(2, new QTableWidgetItem("Property Type"));
		table->horizontalHeader()->setVisible(true);
		table->setStyleSheet("QHeaderView::section {background-color:lightgray}");
		QFont boldFont;
		boldFont.setWeight(QFont::Bold);
		// Iterate over application properties
		int tableRow = 0;
		for (int i = 0; i < 11000; i++) {
			QString nameString;
			QString valueString;
			QString typeString;
			if (getDeviceProperty(deviceItem->openvrId, i, nameString, valueString, typeString)) {
				if (nameString.isEmpty()) {
					nameString = QString::number(i);
				} else {
					nameString = QString::number(i).append(" (").append(nameString).append(")");
				}
				QTableWidgetItem* nameItem = new QTableWidgetItem(nameString);
				nameItem->setFont(boldFont);
				QTableWidgetItem* valueItem = new QTableWidgetItem(valueString);
				QTableWidgetItem* typeItem = new QTableWidgetItem(typeString);
				table->setRowCount(tableRow + 1);
				table->setItem(tableRow, 0, nameItem);
				table->setItem(tableRow, 1, valueItem);
				table->setItem(tableRow, 2, typeItem);
				tableRow++;
			}
		}
	} else {
		mainWindow->setPlainPage("No Connection to OpenVR Runtime.");
	}
}


bool ItemViewModel::getApplicationProperty(const char* appKey, int propId, QString& name, QString& value, QString& type) {
	bool propFound = false;
	vr::EVRApplicationError peError;
	char buffer[vr::k_unMaxApplicationKeyLength];
	auto strcount = vr::VRApplications()->GetApplicationPropertyString(appKey, (vr::EVRApplicationProperty)propId, buffer, vr::k_unMaxApplicationKeyLength, &peError);
	if (peError == vr::VRApplicationError_None && strcount > 0) {
		value = buffer;
		type = "string";
		propFound = true;
	} else {
		auto val = vr::VRApplications()->GetApplicationPropertyBool(appKey, (vr::EVRApplicationProperty)propId, &peError);
		if (peError == vr::VRApplicationError_None) {
			value = val ? "true" : "false";
			type = "bool";
			propFound = true;
		} else {
			auto val = vr::VRApplications()->GetApplicationPropertyUint64(appKey, (vr::EVRApplicationProperty)propId, &peError);
			if (peError == vr::VRApplicationError_None) {
				value = QString::number(val);
				type = "uint64";
				propFound = true;
			}
		}
	}
	if (propFound) {
		auto propNameIt = applicationPropertyNames.find(propId);
		if (propNameIt != applicationPropertyNames.end()) {
			name = QString(propNameIt->second);
		}
	}
	return propFound;
}


bool ItemViewModel::getDeviceProperty(uint32_t deviceId, int propId, QString & name, QString & value, QString & type) {
	bool propFound = false;
	vr::ETrackedPropertyError pError;
	char buffer[vr::k_unMaxPropertyStringSize];
	auto strcount = vr::VRSystem()->GetStringTrackedDeviceProperty(deviceId, (vr::ETrackedDeviceProperty)propId, buffer, vr::k_unMaxPropertyStringSize, &pError);
	if (pError == vr::TrackedProp_Success && strcount > 0) {
		value = buffer;
		type = "string";
		propFound = true;
	} else {
		auto val = vr::VRSystem()->GetBoolTrackedDeviceProperty(deviceId, (vr::ETrackedDeviceProperty)propId, &pError);
		if (pError == vr::TrackedProp_Success) {
			value = val ? "true" : "false";
			type = "bool";
			propFound = true;
		} else {
			auto val = vr::VRSystem()->GetFloatTrackedDeviceProperty(deviceId, (vr::ETrackedDeviceProperty)propId, &pError);
			if (pError == vr::TrackedProp_Success) {
				value = QString::number(val);
				type = "float";
				propFound = true;
			} else {
				auto val = vr::VRSystem()->GetInt32TrackedDeviceProperty(deviceId, (vr::ETrackedDeviceProperty)propId, &pError);
				if (pError == vr::TrackedProp_Success) {
					if (propId == vr::Prop_DeviceClass_Int32) { // device class property
						auto classIt = deviceClassNames.find(val);
						if (classIt != deviceClassNames.end()) {
							value = QString::number(val).append(" (").append(QString(classIt->second)).append(")");
						} else {
							value = QString::number(val);
						}
					} else if (propId >= vr::Prop_Axis0Type_Int32 && propId <= vr::Prop_Axis4Type_Int32) { // axis type properties
						auto axisTypeIt = controllerAxisTypeNames.find(val);
						if (axisTypeIt != controllerAxisTypeNames.end()) {
							value = QString::number(val).append(" (").append(QString(axisTypeIt->second)).append(")");
						} else {
							value = QString::number(val);
						}
					} else if (propId == vr::Prop_ControllerRoleHint_Int32) { // controller role property
						auto roleIt = controllerRoleNames.find(val);
						if (roleIt != controllerRoleNames.end()) {
							value = QString::number(val).append(" (").append(QString(roleIt->second)).append(")");
						} else {
							value = QString::number(val);
						}
					} else {
						value = QString::number(val);
					}
					type = "int32";
					propFound = true;
				} else {
					auto val = vr::VRSystem()->GetUint64TrackedDeviceProperty(deviceId, (vr::ETrackedDeviceProperty)propId, &pError);
					if (pError == vr::TrackedProp_Success) {
						if (propId == vr::Prop_SupportedButtons_Uint64) {
							if (val > 0) {
								value = QString::number(val).append(" (").append(getButtonString(val)).append(")");
							} else {
								value = QString::number(val);
							}
						} else {
							value = QString::number(val);
						}
						type = "uint64";
						propFound = true;
					} else {
						auto val = vr::VRSystem()->GetMatrix34TrackedDeviceProperty(deviceId, (vr::ETrackedDeviceProperty)propId, &pError);
						if (pError == vr::TrackedProp_Success) {
							std::stringstream ss;
							ss << "{ " << val.m[0][0] << ", " << val.m[0][1] << ", " << val.m[0][2] << ", " << val.m[0][3] << "; ";
							ss << val.m[1][0] << ", " << val.m[1][1] << ", " << val.m[1][2] << ", " << val.m[1][3] << "; ";
							ss << val.m[2][0] << ", " << val.m[2][1] << ", " << val.m[2][2] << ", " << val.m[2][3] << " }";
							value = QString::fromStdString(ss.str());
							type = "matrix34";
							propFound = true;
						}
					}
				}
			}
		}
	}
	if (propFound) {
		name = getDevicePropertyName(propId);
	}
	return propFound;
}

QString ItemViewModel::getDevicePropertyName(int propId) {
	QString name;
	auto propNameIt = devicePropertyNames.find(propId);
	if (propNameIt != devicePropertyNames.end()) {
		name = QString(propNameIt->second);
	}
	return name;
}


QString ItemViewModel::getButtonName(uint64_t buttonId) {
	QString buttonString;
	auto buttonIt = buttonNames.find(buttonId);
	if (buttonIt != buttonNames.end()) {
		buttonString.append(buttonIt->second);
	} else {
		buttonString.append("Button_").append(QString::number(buttonId));
	}
	return buttonString;
}


QString ItemViewModel::getButtonString(uint64_t buttonMask) {
	QString buttonString;
	bool isFirst = true;
	for (int i = 0; i < 64; i++) {
		auto button = vr::ButtonMaskFromId((vr::EVRButtonId)i);
		if (buttonMask & button) {
			if (isFirst) {
				isFirst = false;
			} else {
				buttonString.append(" | ");
			}
			buttonString.append(getButtonName(i));
		}
	}
	return buttonString;
}


void ItemViewModel::updateTrackedDevicePage(TrackedDeviceItem* deviceItem) {
	bool isConnected = vr::VRSystem()->IsTrackedDeviceConnected(deviceItem->openvrId);
	deviceItemPage->setIsConnected(isConnected ? "true" : "false");

	auto uraw = deviceItemPage->getSelectedTrackingUniverse();
	vr::ETrackingUniverseOrigin universe;
	switch (uraw) {
	case 0:
		universe = vr::TrackingUniverseStanding;
		break;
	case 1:
		universe = vr::TrackingUniverseSeated;
		break;
	case 2:
		universe = vr::TrackingUniverseRawAndUncalibrated;
		break;
	default:
		universe = vr::TrackingUniverseStanding;
		break;
	}
	vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
	vr::VRSystem()->GetDeviceToAbsoluteTrackingPose(universe, 0.0, poses, vr::k_unMaxTrackedDeviceCount);
	vr::TrackedDevicePose_t* pose = poses + deviceItem->openvrId;
	deviceItemPage->setIsValid(pose->bPoseIsValid ? "true" : "false");
	auto trackingResultIt = trackingResultNames.find(pose->eTrackingResult);
	QString trackingResultText = QString::number(pose->eTrackingResult);
	if (trackingResultIt != trackingResultNames.end()) {
		trackingResultText.append(" (").append(trackingResultIt->second).append(")");
	}
	deviceItemPage->setTrackingResult(trackingResultText);

	if (pose->bPoseIsValid) {
		deviceItemPage->setDevicePos(QString::number(pose->mDeviceToAbsoluteTracking.m[0][3]), 
			QString::number(pose->mDeviceToAbsoluteTracking.m[1][3]), 
			QString::number(pose->mDeviceToAbsoluteTracking.m[2][3]));

		// Hmd Rotation //
		/*
		| Intrinsic y-x'-z" rotation matrix:
		| cr*cy+sp*sr*sy | cr*sp*sy-cy*sr | cp*sy |
		| cp*sr          | cp*cr          |-sp    |
		| cy*sp*sr-cr*sy | cr*cy*sp+sr*sy | cp*cy |

		yaw = atan2(cp*sy, cp*cy) [pi, -pi], CCW
		pitch = -asin(-sp) [pi/2, -pi/2]
		roll = atan2(cp*sr, cp*cr) [pi, -pi], CW
		*/
		auto yaw = std::atan2(pose->mDeviceToAbsoluteTracking.m[0][2], pose->mDeviceToAbsoluteTracking.m[2][2]);
		auto pitch = -std::asin(pose->mDeviceToAbsoluteTracking.m[1][2]);
		auto roll = std::atan2(pose->mDeviceToAbsoluteTracking.m[1][0], pose->mDeviceToAbsoluteTracking.m[1][1]);
		deviceItemPage->setDeviceRot(QString::number(yaw*57.2958).append(QString(0260)), QString::number(pitch* 57.2958).append(QString(0260)), QString::number(roll*57.2958).append(QString(0260)));

		deviceItemPage->setDeviceVel(QString::number(pose->vVelocity.v[0]),
			QString::number(pose->vVelocity.v[1]),
			QString::number(pose->vVelocity.v[2]));

		deviceItemPage->setDeviceAngularVel(QString::number(pose->vAngularVelocity.v[0]),
			QString::number(pose->vAngularVelocity.v[1]),
			QString::number(pose->vAngularVelocity.v[2]));
	} else {
		deviceItemPage->setDevicePos("NA", "NA", "NA");

		deviceItemPage->setDeviceRot("NA", "NA", "NA");

		deviceItemPage->setDeviceVel("NA", "NA", "NA");

		deviceItemPage->setDeviceAngularVel("NA", "NA", "NA");
	}

	vr::VRControllerState_t controllerState;
	if (vr::VRSystem()->GetControllerState(deviceItem->openvrId, &controllerState, sizeof(vr::VRControllerState_t))) {
		QString touchedText = QString::number(controllerState.ulButtonTouched);
		if (controllerState.ulButtonTouched > 0) {
			touchedText.append(" (").append(getButtonString(controllerState.ulButtonTouched)).append(")");
		}
		deviceItemPage->setTouchedButtons(touchedText);
		QString pressedText = QString::number(controllerState.ulButtonPressed);
		if (controllerState.ulButtonPressed > 0) {
			pressedText.append(" (").append(getButtonString(controllerState.ulButtonPressed)).append(")");
		}
		deviceItemPage->setPressedButtons(pressedText);
		deviceItemPage->SetAxis0(QString::number(controllerState.rAxis[0].x), QString::number(controllerState.rAxis[0].y));
		deviceItemPage->SetAxis1(QString::number(controllerState.rAxis[1].x), QString::number(controllerState.rAxis[1].y));
		deviceItemPage->SetAxis2(QString::number(controllerState.rAxis[2].x), QString::number(controllerState.rAxis[2].y));
		deviceItemPage->SetAxis3(QString::number(controllerState.rAxis[3].x), QString::number(controllerState.rAxis[3].y));
		deviceItemPage->SetAxis4(QString::number(controllerState.rAxis[4].x), QString::number(controllerState.rAxis[4].y));
	} else {
		deviceItemPage->setTouchedButtons("NA");
		deviceItemPage->setPressedButtons("NA");
		deviceItemPage->SetAxis0("NA", "NA");
		deviceItemPage->SetAxis1("NA", "NA");
		deviceItemPage->SetAxis2("NA", "NA");
		deviceItemPage->SetAxis3("NA", "NA");
		deviceItemPage->SetAxis4("NA", "NA");
	}
}



void ItemViewModel::handleSaveReport() {
	std::lock_guard<std::recursive_mutex> lock(mutex);
	if (openvrConnected) {
		auto reportPath = QFileDialog::getSaveFileName(mainWindow, QString(), "OpenVR-Report.txt");
		if (!reportPath.isEmpty()) {
			QFile reportFile(reportPath);
			if (reportFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
				QTextStream out(&reportFile);
				out << "Report created on " << QDateTime::currentDateTime().toString("dd.MM.yy hh:mm:ss") << "\n";

				out << "\n====== Tracked Devices ======\n";
				
				vr::TrackedDevicePose_t posesRaw[vr::k_unMaxTrackedDeviceCount];
				vr::VRSystem()->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseRawAndUncalibrated, 0.0, posesRaw, vr::k_unMaxTrackedDeviceCount);

				vr::TrackedDevicePose_t posesStanding[vr::k_unMaxTrackedDeviceCount];
				vr::VRSystem()->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseStanding, 0.0, posesStanding, vr::k_unMaxTrackedDeviceCount);

				vr::TrackedDevicePose_t posesSeated[vr::k_unMaxTrackedDeviceCount];
				vr::VRSystem()->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseSeated, 0.0, posesSeated, vr::k_unMaxTrackedDeviceCount);

				for (auto deviceItem : deviceRootItem->children) {
					auto device = static_cast<TrackedDeviceItem*>(deviceItem.get());
					out << device->openvrId << ": " << QString::fromStdString(device->deviceClassName) << " (" << QString::fromStdString(device->deviceSerial) << "):\n";

					out << "\tisConnected = " << (vr::VRSystem()->IsTrackedDeviceConnected(device->openvrId) ? "true" : "false") << "\n";

					vr::TrackedDevicePose_t* poseRaw = posesRaw + device->openvrId;
					vr::TrackedDevicePose_t* poseStanding = posesStanding + device->openvrId;
					vr::TrackedDevicePose_t* poseSeated = posesSeated + device->openvrId;
					out << "\tPose.isValid = " << (poseRaw->bPoseIsValid ? "true" : "false") << "\n";
					auto trackingResultIt = trackingResultNames.find(poseRaw->eTrackingResult);
					QString trackingResultText = QString::number(poseRaw->eTrackingResult);
					if (trackingResultIt != trackingResultNames.end()) {
						trackingResultText.append(" (").append(trackingResultIt->second).append(")");
					}
					out << "\tPose.trackingResult = " << trackingResultText << "\n";
					if (poseRaw->bPoseIsValid) {
						out << "\tPose.RawUniverse:\n";
						{
							auto& mat = poseRaw->mDeviceToAbsoluteTracking;
							std::stringstream ss;
							ss << "{ " << mat.m[0][0] << ", " << mat.m[0][1] << ", " << mat.m[0][2] << ", " << mat.m[0][3] << "; ";
							ss << mat.m[1][0] << ", " << mat.m[1][1] << ", " << mat.m[1][2] << ", " << mat.m[1][3] << "; ";
							ss << mat.m[2][0] << ", " << mat.m[2][1] << ", " << mat.m[2][2] << ", " << mat.m[2][3] << " }";
							out << "\t\tPositionMatrix = " << QString::fromStdString(ss.str()) << "\n";
						}
						{
							auto& vec = poseRaw->vVelocity;
							out << "\t\tVelocity = " << "{ " << vec.v[0] << ", " << vec.v[1] << ", " << vec.v[2] << " }\n";
						}
						{
							auto& vec = poseRaw->vAngularVelocity;
							out << "\t\tAngularVelocity = " << "{ " << vec.v[0] << ", " << vec.v[1] << ", " << vec.v[2] << " }\n";
						}
						out << "\tPose.StandingUniverse:\n";
						{
							auto& mat = poseStanding->mDeviceToAbsoluteTracking;
							std::stringstream ss;
							ss << "{ " << mat.m[0][0] << ", " << mat.m[0][1] << ", " << mat.m[0][2] << ", " << mat.m[0][3] << "; ";
							ss << mat.m[1][0] << ", " << mat.m[1][1] << ", " << mat.m[1][2] << ", " << mat.m[1][3] << "; ";
							ss << mat.m[2][0] << ", " << mat.m[2][1] << ", " << mat.m[2][2] << ", " << mat.m[2][3] << " }";
							out << "\t\tPositionMatrix = " << QString::fromStdString(ss.str()) << "\n";
						}
						{
							auto& vec = poseStanding->vVelocity;
							out << "\t\tVelocity = " << "{ " << vec.v[0] << ", " << vec.v[1] << ", " << vec.v[2] << " }\n";
						}
						{
							auto& vec = poseStanding->vAngularVelocity;
							out << "\t\tAngularVelocity = " << "{ " << vec.v[0] << ", " << vec.v[1] << ", " << vec.v[2] << " }\n";
						}
						out << "\tPose.SeatedUniverse:\n";
						{
							auto& mat = poseSeated->mDeviceToAbsoluteTracking;
							std::stringstream ss;
							ss << "{ " << mat.m[0][0] << ", " << mat.m[0][1] << ", " << mat.m[0][2] << ", " << mat.m[0][3] << "; ";
							ss << mat.m[1][0] << ", " << mat.m[1][1] << ", " << mat.m[1][2] << ", " << mat.m[1][3] << "; ";
							ss << mat.m[2][0] << ", " << mat.m[2][1] << ", " << mat.m[2][2] << ", " << mat.m[2][3] << " }";
							out << "\t\tPositionMatrix = " << QString::fromStdString(ss.str()) << "\n";
						}
						{
							auto& vec = poseSeated->vVelocity;
							out << "\t\tVelocity = " << "{ " << vec.v[0] << ", " << vec.v[1] << ", " << vec.v[2] << " }\n";
						}
						{
							auto& vec = poseSeated->vAngularVelocity;
							out << "\t\tAngularVelocity = " << "{ " << vec.v[0] << ", " << vec.v[1] << ", " << vec.v[2] << " }\n";
						}
					}
					vr::VRControllerState_t controllerState;
					if (vr::VRSystem()->GetControllerState(device->openvrId, &controllerState, sizeof(vr::VRControllerState_t))) {
						out << "\tControllerState.isValid = true\n";
						QString touchedText = QString::number(controllerState.ulButtonTouched);
						if (controllerState.ulButtonTouched > 0) {
							touchedText.append(" (").append(getButtonString(controllerState.ulButtonTouched)).append(")");
						}
						out << "\tControllerState.ButtonTouched = " << touchedText << "\n";
						QString pressedText = QString::number(controllerState.ulButtonPressed);
						if (controllerState.ulButtonPressed > 0) {
							pressedText.append(" (").append(getButtonString(controllerState.ulButtonPressed)).append(")");
						}
						out << "\tControllerState.ButtonPressed = " << pressedText << "\n";
						out << "\tControllerState.Axis0 = { x = " << QString::number(controllerState.rAxis[0].x) << ", y = " << QString::number(controllerState.rAxis[0].y) << " }\n";
						out << "\tControllerState.Axis1 = { x = " << QString::number(controllerState.rAxis[1].x) << ", y = " << QString::number(controllerState.rAxis[1].y) << " }\n";
						out << "\tControllerState.Axis2 = { x = " << QString::number(controllerState.rAxis[2].x) << ", y = " << QString::number(controllerState.rAxis[2].y) << " }\n";
						out << "\tControllerState.Axis3 = { x = " << QString::number(controllerState.rAxis[3].x) << ", y = " << QString::number(controllerState.rAxis[3].y) << " }\n";
						out << "\tControllerState.Axis4 = { x = " << QString::number(controllerState.rAxis[4].x) << ", y = " << QString::number(controllerState.rAxis[4].y) << " }\n";
					} else {
						out << "\tControllerState.isValid = false\n";
					}
					out << "\tDeviceProperties:\n";
					// Iterate over device properties
					for (int i = 0; i < 11000; i++) {
						QString nameString;
						QString valueString;
						QString typeString;
						if (getDeviceProperty(device->openvrId, i, nameString, valueString, typeString)) {
							if (nameString.isEmpty()) {
								nameString = QString::number(i);
							} else {
								nameString = QString::number(i).append(" (").append(nameString).append(")");
							}
							out << "\t\t" << nameString << " [" << typeString << "] = " << valueString << "\n";
						}
					}
				}

				out << "\n====== Applications ======\n";

				for (auto appItem : applicationsRootItem->children) {
					auto app = static_cast<ApplicationItem*>(appItem.get());
					out << QString::fromStdString(app->key) << ":\n";
					for (int i = 0; i < 255; i++) {
						QString nameString;
						QString valueString;
						QString typeString;
						if (getApplicationProperty(app->key.c_str(), i, nameString, valueString, typeString)) {
							if (nameString.isEmpty()) {
								nameString = QString::number(i);
							} else {
								nameString = QString::number(i).append(" (").append(nameString).append(")");
							}
							out << "\t" << nameString << " [" << typeString << "] = " << valueString << "\n";
						}
					}
				}

				out << "\n====== Drivers ======\n";

				for (auto driverItem : driversRootItem->children) {
					auto driver = static_cast<DriverItem*>(driverItem.get());
					out << QString::fromStdString(driver->name) << "\n";
				}


			} else {
				QMessageBox::warning(nullptr, "Error", "Could not write report to file.");
			}
		}
	}
}
