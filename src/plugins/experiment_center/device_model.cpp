#include <config.h>
#include "device_model.h"

DeviceModel::DeviceModel(Config const &config, Plugins const &plugins, QObject &parent)
    : SlaveItemModel{ config, plugins, &parent }
{
    connect(&_config, &Config::renamed, this, &DeviceModel::updateSlave);
    connect(&_config, &Config::enabled, this, &DeviceModel::updateSlave);
    connect(&_config, &Config::disabled, this, &DeviceModel::updateSlave);
    connect(&_config, &Config::runtimeParamChanged, this, &DeviceModel::updateSlave);
    connect(&config, &Config::updated, this, &DeviceModel::onSlaveUpdated);
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

    switch(index.column())
    {
        case ColumnCaption: return SlaveItemModel::data(index, role);
        case ColumnInfo: return dataInfo(index, role);
        case ColumnState: return dataState(index, role);
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

void DeviceModel::onSlaveUpdated(QUuid const &id)
{

}

QVariant DeviceModel::dataInfo(QModelIndex const &index, int role) const
{
    return {};
}

QVariant DeviceModel::dataState(QModelIndex const &index, int role) const
{
    return {};
}
