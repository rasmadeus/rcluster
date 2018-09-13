#include "device_model.h"

DeviceModel::DeviceModel(Config const &config, Plugins const &plugins, QObject &parent)
    : SlaveCheckModel{ config, plugins, parent }
{
}

QVariant DeviceModel::data(QModelIndex const &index, int role) const
{
    if (role == Qt::CheckStateRole)
        if (!_deviceTypes.contains(slave(index).type()))
            return {};
    return SlaveCheckModel::data(index, role);
}

Qt::ItemFlags DeviceModel::flags(QModelIndex const &index) const
{
    auto flags = SlaveCheckModel::flags(index);
    if (!_deviceTypes.contains(slave(index).type()))
        flags ^= Qt::ItemIsUserCheckable;
    return flags;
}
