#include <unordered_map>
#include <config.h>
#include <slave.h>
#include "devices_model.h"

DevicesModel::DevicesModel(const Config &config, const Plugins &plugins, QObject *parent)
    : QAbstractTableModel{ parent }
    , _config{ config }
    , _plugins{ plugins }
{
    connect(&_config, &Config::renamed, this, &DevicesModel::updateSlave);
    connect(&_config, &Config::enabled, this, &DevicesModel::updateSlave);
    connect(&_config, &Config::disabled, this, &DevicesModel::updateSlave);
    connect(&_config, &Config::runtimeParamChanged, this, &DevicesModel::updateSlave);
}

int DevicesModel::rowCount(QModelIndex const &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(_records.size());
}

int DevicesModel::columnCount(QModelIndex const &parent) const
{
    Q_UNUSED(parent)
    return ColumnSize;
}

QVariant DevicesModel::data(QModelIndex const &index, int role) const
{
    if (!index.isValid())
        return {};

    switch(role)
    {
        case Qt::DisplayRole: return dataDisplayRole(index);
        case Qt::DecorationRole: return dataDecorationRole(index);
        case RoleItemId: return record(index).device();
        default: return {};
    }
}

bool DevicesModel::setData(QModelIndex const &index, QVariant const &value, int role)
{
    Q_UNUSED(index)
    Q_UNUSED(value)
    Q_UNUSED(role)
    return false;
}

QVariant DevicesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical || role != Qt::DisplayRole)
        return {};

    static std::unordered_map<int, QString> headers{
        { ColumnRespondent, tr("Respondent") },
        { ColumnDevice, tr("Device") },
        { ColumnState, tr("State") },
        { ColumnBattery, tr("Battery") },
        { ColumnDataStatus, tr("Data") },
        { ColumnInfo, tr("Info") },
    };

    auto const it = headers.find(section);
    Q_ASSERT(it != headers.cend());
    return it->second;
}

Qt::ItemFlags DevicesModel::flags(QModelIndex const &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void DevicesModel::onSetup(Slave const &slave)
{
    beginResetModel();

    _records.clear();

    for(auto const &place : slave.param(QStringLiteral("respondent_places")).toList())
    {
        auto const respondentPlace = place.toUuid();
        for(auto const &device : _config.slave(respondentPlace).param(QStringLiteral("devices")).toList())
        {
            DeviceRecord record{ _config, _plugins };
            record.setRespondent(respondentPlace);
            record.setDevice(device.toUuid());
            _records.push_back(std::move(record));
        }
    }
    endResetModel();
}

void DevicesModel::updateSlave(QUuid const &slave)
{
    auto const indexes = match(index(0, ColumnRespondent), RoleItemId, slave, -1, Qt::MatchExactly);
    for(auto const& index : indexes)
        emit dataChanged(index, this->index(index.row(), ColumnInfo));
}

QVariant DevicesModel::dataDisplayRole(QModelIndex const &index) const
{
    switch(index.column())
    {
        case ColumnRespondent: return record(index).respondentCaption();
        case ColumnDevice: return record(index).deviceCaption();
        case ColumnState: return record(index).deviceState();
        case ColumnBattery: return record(index).batteryStatus();
        default: return {};
    }
}

QVariant DevicesModel::dataDecorationRole(QModelIndex const &index) const
{
    switch(index.column())
    {
        case ColumnRespondent: return record(index).respondentPixmap();
        case ColumnDevice: return record(index).devicePixmap();
        case ColumnState: return record(index).deviceStatePixmap();
        default: return {};
    }
}
