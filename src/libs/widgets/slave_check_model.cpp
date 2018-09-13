#include <config.h>
#include "slave_check_model.h"

SlaveCheckModel::SlaveCheckModel(Config const &config, Plugins const &plugins, QObject &parent)
    : SlaveModel{ config, plugins, parent }
{
}

Qt::ItemFlags SlaveCheckModel::flags(QModelIndex const &index) const
{
    return SlaveModel::flags(index) | Qt::ItemIsUserCheckable;
}

QVariant SlaveCheckModel::data(QModelIndex const &index, int role) const
{
    if (role == Qt::BackgroundRole)
        return {};

    auto &item = this->item(index);
    return role == Qt::CheckStateRole && index.isValid() ? item.checkState() : SlaveModel::data(index, role);
}

bool SlaveCheckModel::setData(QModelIndex const &index, QVariant const &value, int role)
{
    Q_UNUSED(value)

    if (!index.isValid())
        return false;

    if (role != RoleToggleCheckState)
        return false;

    auto &item = this->item(index);
    item.toggleCheckState();
    updateSlave(item.id());
    return true;
}

void SlaveCheckModel::setChecked(QVariantList const &slaves, SlaveItem &slaveItem)
{
    for(int i = 0; i < slaveItem.childCount(); ++i)
    {
        auto &child = slaveItem.child(i);

        child.setCheckState(slaves.contains(child.id()) ? Qt::Checked : Qt::Unchecked);
        updateSlave(child.id());
        setChecked(slaves, child);
    }
}

QVariantList SlaveCheckModel::checked(SlaveItem const &item) const
{
    QVariantList res;
    for(int i = 0; i < item.childCount(); ++i)
    {
        auto const &child = item.child(i);
        if (child.checkState() == Qt::Checked)
            res << child.id();

        for(auto &&slave : checked(child))
            res << std::move(slave);
    }
    return res;
}

void SlaveCheckModel::setCheckedState(SlaveItem &item, Qt::CheckState state)
{
    for(int i = 0; i < item.childCount(); ++i)
    {
        auto &child = item.child(i);
        child.setCheckState(state);
        updateSlave(child.id());
        setCheckedState(child, state);
    }
}
