#include "node_model.h"
#include "node_sort_model.h"

NodeSortModel::NodeSortModel(QObject &parent)
    : QSortFilterProxyModel{ &parent }
{
}

bool NodeSortModel::lessThan(QModelIndex const &sourceLeft, QModelIndex const &sourceRight) const
{
    auto const leftType = sourceLeft.data(NodeModel::RoleItemType);
    auto const rightType = sourceRight.data(NodeModel::RoleItemType);
    auto const leftCaption = sourceLeft.data();
    auto const rightCaption = sourceRight.data();

    return leftType == rightType ? leftCaption < rightCaption : leftType < rightType;
}
