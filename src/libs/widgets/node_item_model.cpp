#include <config.h>
#include <plugins.h>
#include "node_item_model.h"

NodeItemModel::NodeItemModel(Config const &config, Plugins const &plugins, QObject *parent)
    : QAbstractItemModel{ parent }
    , _config{ config }
    , _plugins{ plugins }
{
}

Qt::ItemFlags NodeItemModel::flags(QModelIndex const &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    auto const item = node(index);
    Qt::ItemFlags flags{ Qt::ItemIsSelectable };

    if (item.enabled())
        flags |= Qt::ItemIsEnabled;

    return flags;
}

QModelIndex NodeItemModel::index(int row, int column, QModelIndex const &parent) const
{
    auto &parentItem = item(parent);

    if (parentItem.isChildless())
        return {};

    if (!parentItem.hasChild(row))
        return {};

    auto &childItem = parentItem.child(row);
    return createIndex(row, column, &childItem);
}

QModelIndex NodeItemModel::parent(QModelIndex const &index) const
{
    auto &childItem = item(index);

    if (&childItem == &_root)
        return {};

    auto parentItem = childItem.parent();
    if (parentItem == &_root)
        return {};

    return createIndex(parentItem->posAmongSiblings(), ColumnCaption, parentItem);
}

int NodeItemModel::rowCount([[maybe_unused]] QModelIndex const &parent) const
{
    return item(parent).childCount();
}

int NodeItemModel::columnCount([[maybe_unused]] QModelIndex const &parent) const
{
    return ColumnCaption + 1;
}

QVariant NodeItemModel::data(QModelIndex const &index, int role) const
{
    if (!index.isValid())
        return {};

    switch(role)
    {
        case Qt::ToolTipRole:
        case Qt::DisplayRole: return node(index).name();
        case Qt::DecorationRole: return _plugins.plugin(node(index).type())->pixmap();
        case RoleItemId: return item(index).id();
        case RoleItemType: return node(index).type();
        default: return {};
    }
}

NodeItem &NodeItemModel::item(QModelIndex const &index) const
{
    return index.isValid()
        ? *(static_cast<NodeItem*>(index.internalPointer()))
        : const_cast<NodeItem&>(_root);
}

Node NodeItemModel::node(QModelIndex const &index) const
{
    Q_ASSERT(index.isValid());
    return _config.node(item(index).id());
}

void NodeItemModel::appendNode(QUuid const &node)
{
    auto const parent = _config.node(node).parent();
    auto const indexes = match(index(0, ColumnCaption), RoleItemId, parent, 1, Qt::MatchRecursive);
    auto const parentIndex = indexes.isEmpty() ? QModelIndex{} : indexes.first();
    auto &parentItem = item(parentIndex);
    auto const pos = parentItem.childCount();

    beginInsertRows(parentIndex, pos, pos);
    parentItem.append(node);
    endInsertRows();
}

void NodeItemModel::removeNode(QUuid const &node)
{
    auto const indexes = match(index(0, ColumnCaption), RoleItemId, node, 1, Qt::MatchRecursive);
    Q_ASSERT(!indexes.isEmpty());

    auto parentItem = item(indexes.first()).parent();
    auto const pos = parentItem->childPos(node);

    auto const parentIndexes = match(index(0, ColumnCaption), RoleItemId, parentItem->id(), 1, Qt::MatchRecursive);
    auto const parentIndex = parentIndexes.isEmpty() ? QModelIndex{} : parentIndexes.first();

    beginRemoveRows(parentIndex, pos, pos);
    parentItem->remove(pos);
    endRemoveRows();
}

void NodeItemModel::updateNode(QUuid const &node)
{
    auto const indexes = match(index(0, ColumnCaption), RoleItemId, node, -1, Qt::MatchRecursive);
    for(auto const& index : indexes)
        emit dataChanged(index, this->index(index.row(), columnCount(index.parent()) - 1, index.parent()));
}
