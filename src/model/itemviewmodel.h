#pragma once
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QTimer>
#include <vector>
#include <memory>
#include <mutex>
#include <openvr.h>

class MainWindow;
class DeviceItemPage;


enum class ItemType : uint32_t {
	Invalid = 0,
	TreeNode = 1,
	TrackedDevice = 2,
	Driver = 3,
	Application = 4,
};


struct AbstractItem {
	const ItemType itemType;
	AbstractItem* parent = nullptr;
	std::vector<std::shared_ptr<AbstractItem>> children;
	int row = 0;

	AbstractItem(ItemType type = ItemType::Invalid) : itemType(type) {}
	virtual ~AbstractItem() {
		children.clear();
	}

	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const = 0;

	void addChild(AbstractItem* child) {
		child->parent = this;
		child->row = (int)children.size();
		children.push_back(std::shared_ptr<AbstractItem>(child));
	}
	void addChild(std::shared_ptr<AbstractItem> child) {
		child->parent = this;
		child->row = (int)children.size();
		children.push_back(child);
	}

	template<class _T>
	_T& as() {
		return *static_cast<_T*>(this);
	}
	template<class _T>
	const _T& as() const {
		return *static_cast<_T*>(this);
	}
};


struct TreeNode : public AbstractItem {
	QVariant text;

	TreeNode() : AbstractItem(ItemType::TreeNode) {}
	TreeNode(QVariant text) : AbstractItem(ItemType::TreeNode), text(text) {}

	virtual QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const {
		switch (role) {
		case Qt::DisplayRole:
			return text;
		break;
		default:
			return QVariant();
		}
	}
};


struct TrackedDeviceItem : public AbstractItem {
	std::string displayName;
	uint32_t openvrId;
	int deviceClass = 0;
	std::string deviceClassName;
	std::string deviceSerial;

	TrackedDeviceItem() : AbstractItem(ItemType::TrackedDevice) {}

	virtual QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const {
		switch (role) {
		case Qt::DisplayRole:
			return QString::fromStdString(displayName);
			break;
		default:
			return QVariant();
		}
	}
};


struct ApplicationItem : public AbstractItem {
	std::string key;
	uint32_t index = 0;

	ApplicationItem() : AbstractItem(ItemType::Application) {}

	virtual QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const {
		switch (role) {
		case Qt::DisplayRole:
			return QString::fromStdString(key);
			break;
		default:
			return QVariant();
		}
	}
};


struct DriverItem : public AbstractItem {
	std::string name;
	uint32_t index = 0;

	DriverItem() : AbstractItem(ItemType::Driver) {}

	virtual QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const {
		switch (role) {
		case Qt::DisplayRole:
			return QString::fromStdString(name);
			break;
		default:
			return QVariant();
		}
	}
};




class ItemViewModel : public QAbstractItemModel {
	Q_OBJECT

public:
	ItemViewModel(MainWindow* mainWindow, QObject * parent = Q_NULLPTR);
	~ItemViewModel();

	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	virtual QModelIndex parent(const QModelIndex &index) const override;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	void currentItemChanged(const QModelIndex &current, const QModelIndex &previous);

	void expandRootItems();
	void reloadTrackedDevices();
	void reloadDrivers();
	void reloadApplications();

public slots:
	void shutdown();
	void handleSaveReport();

	void onTimerEvent();

private:
	MainWindow* mainWindow;
	TreeNode rootItem;
	bool openvrConnected = true;
	std::recursive_mutex mutex;
	std::shared_ptr<AbstractItem> deviceRootItem;
	std::shared_ptr<AbstractItem> driversRootItem;
	std::shared_ptr<AbstractItem> applicationsRootItem;

	QTimer eventTimer;
	AbstractItem* activeItem = nullptr;
	DeviceItemPage* deviceItemPage = nullptr;

	static std::map<int, const char*> applicationPropertyNames;
	static std::map<int, const char*> devicePropertyNames;
	static std::map<int, const char*> controllerAxisTypeNames;
	static std::map<int, const char*> controllerRoleNames;
	static std::map<int, const char*> deviceClassNames;
	static std::map<int, const char*> buttonNames;
	static std::map<int, const char*> trackingResultNames;

	void handleApplicationItemSelected(ApplicationItem* appItem);
	void handleTrackedDeviceItemSelected(TrackedDeviceItem* deviceItem);

	bool getApplicationProperty(const char* appKey, int propId, QString & name, QString & value, QString & type);
	bool getDeviceProperty(uint32_t deviceId, int propId, QString & name, QString & value, QString & type);
	QString getDevicePropertyName(int propid);

	QString getButtonString(uint64_t buttonMask);
	QString getButtonName(uint64_t buttonId);

	void updateTrackedDevicePage(TrackedDeviceItem* deviceItem);
};
