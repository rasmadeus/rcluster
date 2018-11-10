#ifndef SLAVEMODEL_H
#define SLAVEMODEL_H

#include "node_item_model.h"

class WIDGETS_SHARED_EXPORT NodeModel : public NodeItemModel
{
    Q_OBJECT

public:
    explicit NodeModel(Config const &config, Plugins const &plugins, QObject &parent);

public:
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;

signals:
    void reloaded();
    void renamed(QUuid const &node);

protected:
    void appendNodeById(QUuid const &id);
    void appendChildren(QUuid const &id, NodeItem &item);
    void reloadNodes();

    QVariant dataBackground(QModelIndex const &index) const;
    QVariant dataTextColor(QModelIndex const &index) const;
};

#endif // SLAVEMODEL_H
