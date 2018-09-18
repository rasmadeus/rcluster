#include <config.h>
#include <svg.h>
#include <device_state.h>
#include "device_model.h"

DeviceModel::DeviceModel(Config const &config, Plugins const &plugins, QObject &parent)
    : SlaveItemModel{ config, plugins, &parent }
{
    connect(&_config, &Config::renamed, this, &DeviceModel::updateSlave);
    connect(&_config, &Config::enabled, this, &DeviceModel::updateSlave);
    connect(&_config, &Config::disabled, this, &DeviceModel::updateSlave);
    connect(&_config, &Config::runtimeParamChanged, this, &DeviceModel::updateSlave);
}

int DeviceModel::columnCount(QModelIndex const &parent) const
{
    Q_UNUSED(parent)
    return ColumnSize;
}

QVariant DeviceModel::data(QModelIndex const &index, int role) const
{
    if (!index.isValid())
        return {};

    switch(role)
    {
        case Qt::ToolTipRole:
        case Qt::DisplayRole: return dataDisplay(index);
        case Qt::DecorationRole: return dataDecoration(index);
        case RoleItemId: return item(index).id();
        case RoleItemType: return slave(index).type();
        default: return {};
    }
}

void DeviceModel::onSetup(Slave const &slave)
{
    beginResetModel();
    _root.clear();
    for(auto const &place : slave.param(QStringLiteral("respondent_places")).toList())
    {
        _root.append(place.toUuid());
        auto &lastPlace = _root.lastChild();
        for(auto const &device : _config.slave(place.toUuid()).param(QStringLiteral("devices")).toList())
            lastPlace.append(device.toUuid());
    }
    endResetModel();
}

QVariant DeviceModel::dataDisplay(QModelIndex const &index) const
{
    switch(index.column())
    {
        case ColumnCaption: return SlaveItemModel::data(index);
        case ColumnInfo: return {};
        default: return {};
    }
}

QVariant DeviceModel::dataDecoration(QModelIndex const &index) const
{
    if (index.column() == ColumnCaption)
        return SlaveItemModel::data(index, Qt::DecorationRole);

    return {};
}
