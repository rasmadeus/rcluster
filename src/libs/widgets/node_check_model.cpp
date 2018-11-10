#include <config.h>
#include "node_check_model.h"

NodeCheckModel::NodeCheckModel(Config const &config, Plugins const &plugins, QObject &parent)
    : NodeModel{ config, plugins, parent }
{
}

Qt::ItemFlags NodeCheckModel::flags(QModelIndex const &index) const
{
    return NodeModel::flags(index) | Qt::ItemIsUserCheckable;
}

QVariant NodeCheckModel::data(QModelIndex const &index, int role) const
{
    if (role == Qt::BackgroundRole)
        return {};

    auto &item = this->item(index);
    return role == Qt::CheckStateRole && index.isValid() ? item.checkState() : NodeModel::data(index, role);
}

bool NodeCheckModel::setData(QModelIndex const &index, [[maybe_unused]] QVariant const &value, int role)
{
    if (!index.isValid())
        return false;

    if (role != RoleToggleCheckState)
        return false;

    auto &item = this->item(index);
    item.toggleCheckState();
    updateNode(item.id());
    return true;
}

void NodeCheckModel::setChecked(QVariantList const &nodes, NodeItem &nodeItem)
{
    for(int i = 0; i < nodeItem.childCount(); ++i)
    {
        auto &child = nodeItem.child(i);
        auto const needCheck = std::any_of(nodes.cbegin(), nodes.cend(), [&child](auto const &item){ return item.toUuid() == child.id(); });
        child.setCheckState(needCheck ? Qt::Checked : Qt::Unchecked);
        updateNode(child.id());
        setChecked(nodes, child);
    }
}

QVariantList NodeCheckModel::checked(NodeItem const &item) const
{
    QVariantList res;
    for(int i = 0; i < item.childCount(); ++i)
    {
        auto const &child = item.child(i);
        if (child.checkState() == Qt::Checked)
            res << child.id();

        for(auto &&node : checked(child))
            res << std::move(node);
    }
    return res;
}

void NodeCheckModel::setCheckedState(NodeItem &item, Qt::CheckState state)
{
    for(int i = 0; i < item.childCount(); ++i)
    {
        auto &child = item.child(i);
        child.setCheckState(state);
        updateNode(child.id());
        setCheckedState(child, state);
    }
}
