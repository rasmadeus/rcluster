#include "device_model.h"

DeviceModel::DeviceModel(Config const &config, Plugins const &plugins, QObject &parent)
    : SlaveModelCheck{ config, plugins, parent }
{
}

QVariant DeviceModel::data(QModelIndex const &index, int role) const
{
    if (role == Qt::CheckStateRole)
        if (!_deviceTypes.contains(slave(index).type()))
            return {};
    return SlaveModelCheck::data(index, role);
}

Qt::ItemFlags DeviceModel::flags(QModelIndex const &index) const
{
    auto flags = SlaveModelCheck::flags(index);
    if (!_deviceTypes.contains(slave(index).type()))
        flags ^= Qt::ItemIsUserCheckable;
    return flags;
}
