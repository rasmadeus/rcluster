#ifndef SLAVE_ITEM_MODEL_H
#define SLAVE_ITEM_MODEL_H

#include <QAbstractItemModel>
#include <slave.h>
#include <slave_item.h>
#include "widgets_global.h"

class Config;
class Plugins;

class WIDGETS_SHARED_EXPORT SlaveItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum
    {
        ColumnCaption,
    };

    enum
    {
        RoleItemId = Qt::UserRole + 1,
        RoleItemType,
    };

public:
    explicit SlaveItemModel(Config const &config, Plugins const &plugins, QObject *parent = nullptr);

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

protected:
    void appendSlave(QUuid const &slave);
    void removeSlave(QUuid const &slave);
    void updateSlave(QUuid const &slave);

protected:
    Config const &_config;
    Plugins const &_plugins;
    SlaveItem _root;
};

#endif // SLAVE_ITEM_MODEL_H