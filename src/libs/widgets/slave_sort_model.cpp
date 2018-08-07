#include "slave_model.h"
#include "slave_sort_model.h"

SlaveSortModel::SlaveSortModel(QObject &parent)
    : QSortFilterProxyModel{ &parent }
{
}

bool SlaveSortModel::lessThan(QModelIndex const &sourceLeft, QModelIndex const &sourceRight) const
{
    auto const leftType = sourceLeft.data(SlaveModel::RoleItemType);
    auto const rightType = sourceRight.data(SlaveModel::RoleItemType);
    auto const leftCaption = sourceLeft.data();
    auto const rightCaption = sourceRight.data();

    return leftType == rightType
        ? leftCaption.toString().localeAwareCompare(rightCaption.toString())
        : leftType.toString().localeAwareCompare(rightType.toString());
}
