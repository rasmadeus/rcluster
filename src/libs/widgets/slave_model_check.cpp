#include <config.h>
#include "slave_model_check.h"

SlaveModelCheck::SlaveModelCheck(Config const &config, Plugins const &plugins, QObject &parent)
    : SlaveModel{ config, plugins, parent }
{
}

void SlaveModelCheck::setSlave(QUuid const &slave)
{
    _slave = slave;
}

Qt::ItemFlags SlaveModelCheck::flags(QModelIndex const &index) const
{
    auto flags = SlaveModel::flags(index);
    if (!_slave.isNull() && item(index).id() != _slave)
        flags |= Qt::ItemIsUserCheckable;
    return flags;
}

QVariant SlaveModelCheck::data(QModelIndex const &index, int role) const
{
    if (role == Qt::BackgroundRole)
        return {};

    auto &item = this->item(index);
    return role == Qt::CheckStateRole && index.isValid() && item.id() != _slave
        ? item.checkState()
        : SlaveModel::data(index, role);
}

bool SlaveModelCheck::setData(QModelIndex const &index, QVariant const &value, int role)
{
    Q_UNUSED(value)

    if (!index.isValid())
        return false;

    if (role != RoleToggleCheckState)
        return false;

    if (_slave.isNull())
        return false;

    auto &item = this->item(index);
    item.toggleCheckState();
    updateSlave(item.id());
    return true;
}

void SlaveModelCheck::setChecked(QSet<QUuid> const &slaves, SlaveItem &slaveItem)
{
    for(int i = 0; i < slaveItem.childCount(); ++i)
    {
        auto &child = slaveItem.child(i);

        if (child.id() == _slave)
            continue;

        child.setCheckState(slaves.contains(child.id()) ? Qt::Checked : Qt::Unchecked);
        updateSlave(child.id());
        setChecked(slaves, child);
    }
}

QSet<QUuid> SlaveModelCheck::checked(SlaveItem const &item) const
{
    QSet<QUuid> res;
    for(int i = 0; i < item.childCount(); ++i)
    {
        auto const &child = item.child(i);
        if (child.checkState() == Qt::Checked)
            res.insert(child.id());

        for(auto &&slave : checked(child))
            res.insert(std::move(slave));
    }
    return res;
}

void SlaveModelCheck::setCheckedState(SlaveItem &item, Qt::CheckState state)
{
    for(int i = 0; i < item.childCount(); ++i)
    {
        auto &child = item.child(i);
        child.setCheckState(state);
        updateSlave(child.id());
        setCheckedState(child, state);
    }
}
