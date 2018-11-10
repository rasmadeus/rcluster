#include "node_check_model.h"
#include "node_type_proxy_model.h"

NodeTypeProxyModel::NodeTypeProxyModel(QStringList const &types, QStringList const &checkableTypes, QObject &parent)
    : NodeSortModel{ parent }
    , _types{ types }
    , _checkableTypes{ checkableTypes }
{
}

QVariant NodeTypeProxyModel::data(QModelIndex const &index, int role) const
{
    if (role == Qt::CheckStateRole)
    {
        auto const type = index.data(NodeModel::RoleItemType).toString();
        if (!_checkableTypes.contains(type))
            return {};
    }
    return NodeSortModel::data(index, role);
}

Qt::ItemFlags NodeTypeProxyModel::flags(QModelIndex const &index) const
{
    auto flags = NodeSortModel::flags(index);
    auto const type = index.data(NodeModel::RoleItemType).toString();
    if (!_checkableTypes.contains(type))
        flags ^= Qt::ItemIsUserCheckable;
    return flags;
}

bool NodeTypeProxyModel::setData(QModelIndex const &index, QVariant const &value, int role)
{
    if (role == NodeCheckModel::RoleToggleCheckState)
    {
        auto const type = index.data(NodeModel::RoleItemType).toString();
        if (!_checkableTypes.contains(type))
            return false;
    }
    return NodeSortModel::setData(index, value, role);
}

bool NodeTypeProxyModel::filterAcceptsRow(int sourceRow, QModelIndex const &sourceParent) const
{
    auto const type = sourceModel()->index(sourceRow, NodeModel::ColumnCaption, sourceParent).data(NodeModel::RoleItemType).toString();
    return _types.contains(type) || _checkableTypes.contains(type);
}
