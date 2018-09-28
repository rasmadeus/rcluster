#ifndef DEVICES_MODEL_H
#define DEVICES_MODEL_H

#include <vector>
#include <QAbstractTableModel>
#include "device_record.h"

class Config;
class Plugins;
class Slave;

class DevicesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum
    {
        ColumnRespondent,
        ColumnDevice,
        ColumnState,
        ColumnBattery,
        ColumnDataStatus,
        ColumnInfo,
        ColumnSize,
    };

    enum
    {
        RoleItemId = Qt::UserRole + 1,
    };

public:
    explicit DevicesModel(Config const &config, Plugins const &plugins, QObject *parent = nullptr);

public:
    int rowCount(QModelIndex const &parent = {}) const override;
    int columnCount(QModelIndex const &parent = {}) const override;
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;
    bool setData(QModelIndex const &index, QVariant const &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(QModelIndex const &index) const override;

public:
    void onSetup(Slave const &slave);

private:
    void updateSlave(QUuid const &slave);
    DeviceRecord const &record(QModelIndex const &index) const { return _records[static_cast<std::size_t>(index.row())]; }
    QVariant dataDisplayRole(QModelIndex const &index) const;
    QVariant dataDecorationRole(QModelIndex const &index) const;

private:
    Config const &_config;
    Plugins const &_plugins;

    std::vector<DeviceRecord> _records;
};

#endif // DEVICES_MODEL_H
