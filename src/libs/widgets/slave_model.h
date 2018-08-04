#ifndef SLAVEMODEL_H
#define SLAVEMODEL_H

#include <QAbstractItemModel>
#include <slave.h>
#include "slave_item.h"
#include "widgets_global.h"

class Config;
class Plugins;

class WIDGETS_SHARED_EXPORT SlaveModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum
    {
        ColumnCaption,
        ColumnSize,
    };

    enum
    {
        RoleItemId = Qt::UserRole + 1,
        RoleItemType,
    };

public:
    explicit SlaveModel(Config const &config, Plugins const &plugins, QObject &parent);

public:
    Qt::ItemFlags flags(QModelIndex const &index) const override;
    QModelIndex index(int row, int column, QModelIndex const &parent = {}) const override;
    QModelIndex parent(QModelIndex const &index) const override;
    int rowCount(QModelIndex const &parent = {}) const override;
    int columnCount(QModelIndex const &parent = {}) const override;
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;

protected:
    SlaveItem &item(QModelIndex const &index) const;
    Slave slave(QModelIndex const &index) const;
    void appendChildren(QUuid const &id, SlaveItem &item);

    void reloadSlaves();

    void appendSlave(QUuid const &slave);
    void removeSlave(QUuid const &slave);
    void updateSlave(QUuid const &slave);

protected:
    Config const &_config;
    Plugins const &_plugins;
    SlaveItem _root;
};

#endif // SLAVEMODEL_H
