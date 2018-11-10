#ifndef SLAVE_ITEM_MODEL_H
#define SLAVE_ITEM_MODEL_H

#include <QAbstractItemModel>
#include <node.h>
#include <node_item.h>
#include "widgets_global.h"

class Config;
class Plugins;

class WIDGETS_SHARED_EXPORT NodeItemModel : public QAbstractItemModel
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
    explicit NodeItemModel(Config const &config, Plugins const &plugins, QObject *parent = nullptr);

public:
    Qt::ItemFlags flags(QModelIndex const &index) const override;
    QModelIndex index(int row, int column, QModelIndex const &parent = {}) const override;
    QModelIndex parent(QModelIndex const &index) const override;
    int rowCount(QModelIndex const &parent = {}) const override;
    int columnCount(QModelIndex const &parent = {}) const override;
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;

protected:
    NodeItem &item(QModelIndex const &index) const;
    Node node(QModelIndex const &index) const;

protected:
    void appendNode(QUuid const &node);
    void removeNode(QUuid const &node);
    void updateNode(QUuid const &node);

protected:
    Config const &_config;
    Plugins const &_plugins;
    NodeItem _root;
};

#endif // SLAVE_ITEM_MODEL_H
