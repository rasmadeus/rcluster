#include <config.h>
#include <plugins.h>
#include "slave_item_model.h"

SlaveItemModel::SlaveItemModel(Config const &config, Plugins const &plugins, QObject *parent)
    : QAbstractItemModel{ parent }
    , _config{ config }
    , _plugins{ plugins }
{
}

Qt::ItemFlags SlaveItemModel::flags(QModelIndex const &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    auto const item = slave(index);
    Qt::ItemFlags flags{ Qt::ItemIsSelectable };

    if (item.enabled())
        flags |= Qt::ItemIsEnabled;

    return flags;
}

QModelIndex SlaveItemModel::index(int row, int column, QModelIndex const &parent) const
{
    auto &parentItem = item(parent);

    if (parentItem.isChildless())
        return {};

    if (!parentItem.hasChild(row))
        return {};

    auto &childItem = parentItem.child(row);
    return createIndex(row, column, &childItem);
}

QModelIndex SlaveItemModel::parent(QModelIndex const &index) const
{
    auto &childItem = item(index);

    if (&childItem == &_root)
        return {};

    auto parentItem = childItem.parent();
    if (parentItem == &_root)
        return {};

    return createIndex(parentItem->posAmongSiblings(), ColumnCaption, parentItem);
}

int SlaveItemModel::rowCount(QModelIndex const &parent) const
{
    return item(parent).childCount();
}

int SlaveItemModel::columnCount(QModelIndex const &parent) const
{
    Q_UNUSED(parent)
    return ColumnCaption + 1;
}

QVariant SlaveItemModel::data(QModelIndex const &index, int role) const
{
    if (!index.isValid())
        return {};

    switch(role)
    {
        case Qt::ToolTipRole:
        case Qt::DisplayRole: return slave(index).name();
        case Qt::DecorationRole: return _plugins.plugin(slave(index).type())->pixmap();
        case RoleItemId: return item(index).id();
        case RoleItemType: return slave(index).type();
        default: return {};
    }
}

SlaveItem &SlaveItemModel::item(QModelIndex const &index) const
{
    return index.isValid()
        ? *(static_cast<SlaveItem*>(index.internalPointer()))
        : const_cast<SlaveItem&>(_root);
}

Slave SlaveItemModel::slave(QModelIndex const &index) const
{
    Q_ASSERT(index.isValid());
    return _config.slave(item(index).id());
}

void SlaveItemModel::appendSlave(QUuid const &slave)
{
    auto const parent = _config.slave(slave).parent();
    auto const indexes = match(index(0, ColumnCaption), RoleItemId, parent, 1, Qt::MatchRecursive);
    auto const parentIndex = indexes.isEmpty() ? QModelIndex{} : indexes.first();
    auto &parentItem = item(parentIndex);
    auto const pos = parentItem.childCount();

    beginInsertRows(parentIndex, pos, pos);
    parentItem.append(slave);
    endInsertRows();
}

void SlaveItemModel::removeSlave(QUuid const &slave)
{
    auto const indexes = match(index(0, ColumnCaption), RoleItemId, slave, 1, Qt::MatchRecursive);
    Q_ASSERT(!indexes.isEmpty());

    auto parentItem = item(indexes.first()).parent();
    auto const pos = parentItem->childPos(slave);

    auto const parentIndexes = match(index(0, ColumnCaption), RoleItemId, parentItem->id(), 1, Qt::MatchRecursive);
    auto const parentIndex = parentIndexes.isEmpty() ? QModelIndex{} : parentIndexes.first();

    beginRemoveRows(parentIndex, pos, pos);
    parentItem->remove(pos);
    endRemoveRows();
}

void SlaveItemModel::updateSlave(QUuid const &slave)
{
    auto const indexes = match(index(0, ColumnCaption), RoleItemId, slave, -1, Qt::MatchRecursive);
    for(auto const& index : indexes)
        emit dataChanged(index, index);
}
