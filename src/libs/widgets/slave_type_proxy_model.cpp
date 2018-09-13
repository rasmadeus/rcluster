#include "slave_model.h"
#include "slave_type_proxy_model.h"

SlaveTypeProxyModel::SlaveTypeProxyModel(QStringList const &types, QStringList const &checkableTypes, QObject &parent)
    : SlaveSortModel{ parent }
    , _types{ types }
    , _checkableTypes{ checkableTypes }
{
}

QVariant SlaveTypeProxyModel::data(QModelIndex const &index, int role) const
{
    if (role == Qt::CheckStateRole)
    {
        auto const type = index.data(SlaveModel::RoleItemType).toString();
        if (!_checkableTypes.contains(type))
            return {};
    }
    return SlaveSortModel::data(index, role);
}

Qt::ItemFlags SlaveTypeProxyModel::flags(QModelIndex const &index) const
{
    auto flags = SlaveSortModel::flags(index);
    auto const type = index.data(SlaveModel::RoleItemType).toString();
    if (!_checkableTypes.contains(type))
        flags ^= Qt::ItemIsUserCheckable;
    return flags;
}

bool SlaveTypeProxyModel::filterAcceptsRow(int sourceRow, QModelIndex const &sourceParent) const
{
    auto const type = sourceModel()->index(sourceRow, SlaveModel::ColumnCaption, sourceParent).data(SlaveModel::RoleItemType).toString();
    return _types.contains(type) || _checkableTypes.contains(type);
}
