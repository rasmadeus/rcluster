#include <unordered_map>
#include <QDebug>
#include "config.h"
#include <plugins.h>
#include "slave_model.h"

SlaveModel::SlaveModel(Config const &config, Plugins const &plugins, QObject &parent)
    : QAbstractItemModel{ &parent }
    , _config{ config }
    , _plugins{ plugins }
{
    reloadSlaves();

    connect(&_config, &Config::reseted, this, &SlaveModel::reloadSlaves);
    connect(&_config, &Config::appended, this, &SlaveModel::appendSlave);
    connect(&_config, &Config::removeFinished, this, &SlaveModel::removeSlave);
    connect(&_config, &Config::renamed, this, &SlaveModel::updateSlave);
    connect(&_config, &Config::enabled, this, &SlaveModel::updateSlave);
    connect(&_config, &Config::disabled, this, &SlaveModel::updateSlave);
    connect(&_config, &Config::updated, this, &SlaveModel::updateSlave);
    connect(&_config, &Config::processStateChanged, this, &SlaveModel::updateSlave);
}

Qt::ItemFlags SlaveModel::flags(QModelIndex const &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    auto const item = slave(index);
    Qt::ItemFlags flags{ Qt::ItemIsSelectable };

    if (item.enabled())
        flags |= Qt::ItemIsEnabled;

    return flags;
}

QModelIndex SlaveModel::index(int row, int column, QModelIndex const &parent) const
{
    auto &parentItem = item(parent);

    if (parentItem.isChildless())
        return {};

    if (!parentItem.hasChild(row))
        return {};

    auto &childItem = parentItem.child(row);
    return createIndex(row, column, &childItem);
}

QModelIndex SlaveModel::parent(QModelIndex const &index) const
{
    auto &childItem = item(index);

    if (&childItem == &_root)
        return {};

    auto parentItem = childItem.parent();
    if (parentItem == &_root)
        return {};

    return createIndex(parentItem->posAmongSiblings(), ColumnCaption, parentItem);
}

int SlaveModel::rowCount(QModelIndex const &parent) const
{
    return item(parent).childCount();
}

int SlaveModel::columnCount(QModelIndex const &parent) const
{
    Q_UNUSED(parent)
    return ColumnSize;
}

QVariant SlaveModel::data(QModelIndex const &index, int role) const
{
    if (!index.isValid())
        return {};

    switch(role)
    {
        case Qt::ToolTipRole:
        case Qt::DisplayRole: return slave(index).name();
        case Qt::DecorationRole: return _plugins.plugin(slave(index).type())->pixmap();
        case Qt::BackgroundRole: return dataBackground(index);
        case RoleItemId: return item(index).id();
        case RoleItemType: return _config.slave(item(index).id()).type();
        default: return {};
    }
}

SlaveItem &SlaveModel::item(QModelIndex const &index) const
{
    return index.isValid()
        ? *(static_cast<SlaveItem*>(index.internalPointer()))
        : const_cast<SlaveItem&>(_root);
}

Slave SlaveModel::slave(QModelIndex const &index) const
{
    Q_ASSERT(index.isValid());
    return _config.slave(index.data(RoleItemId).toUuid());
}

void SlaveModel::appendChildren(QUuid const &id, SlaveItem &item)
{
    for(auto const &child : _config.children(id))
    {
        item.append(child);
        appendChildren(child, item.lastChild());
    }
}

void SlaveModel::reloadSlaves()
{
    beginResetModel();
    _root.clear();
    appendChildren({}, _root);
    endResetModel();
    emit reloaded();
}

void SlaveModel::appendSlave(QUuid const &slave)
{
    auto const parent = _config.slave(slave).parent();
    auto const indexes = match(index(0, ColumnCaption), SlaveModel::RoleItemId, parent, 1, Qt::MatchRecursive);
    auto const parentIndex = indexes.isEmpty() ? QModelIndex{} : indexes.first();
    auto &parentItem = item(parentIndex);
    auto const pos = parentItem.childCount();

    beginInsertRows(parentIndex, pos, pos);
    parentItem.append(slave);
    endInsertRows();
}

void SlaveModel::removeSlave(QUuid const &slave)
{
    auto const indexes = match(index(0, ColumnCaption), SlaveModel::RoleItemId, slave, 1, Qt::MatchRecursive);
    Q_ASSERT(!indexes.isEmpty());

    auto parentItem = item(indexes.first()).parent();
    auto const pos = parentItem->childPos(slave);

    auto const parentIndexes = match(index(0, ColumnCaption), SlaveModel::RoleItemId, parentItem->id(), 1, Qt::MatchRecursive);
    auto const parentIndex = parentIndexes.isEmpty() ? QModelIndex{} : parentIndexes.first();

    beginRemoveRows(parentIndex, pos, pos);
    parentItem->remove(pos);
    endRemoveRows();
}

void SlaveModel::updateSlave(QUuid const &slave)
{
    auto const indexes = match(index(0, ColumnCaption), SlaveModel::RoleItemId, slave, 1, Qt::MatchRecursive);
    Q_ASSERT(!indexes.isEmpty());
    emit dataChanged(indexes.first(), indexes.first());
}

QVariant SlaveModel::dataBackground(QModelIndex const &index) const
{
    auto const slave = this->slave(index);
    if (!_plugins.plugin(slave.type())->hasProcess() || slave.disabled())
        return {};

    switch(slave.processState())
    {
        case QProcess::ProcessState::NotRunning: return QColor{ 255, 150, 150 };
        case QProcess::ProcessState::Starting : return QColor{ 150, 250, 150 };
        case QProcess::ProcessState::Running: return {};
    }

    Q_ASSERT(false);
    return {};
}
