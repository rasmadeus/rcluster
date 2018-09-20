#ifndef SLAVEMODEL_H
#define SLAVEMODEL_H

#include "slave_item_model.h"

class WIDGETS_SHARED_EXPORT SlaveModel : public SlaveItemModel
{
    Q_OBJECT

public:
    explicit SlaveModel(Config const &config, Plugins const &plugins, QObject &parent);

public:
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;

signals:
    void reloaded();
    void renamed(QUuid const &slave);

protected:
    void appendSlaveById(QUuid const &id);
    void appendChildren(QUuid const &id, SlaveItem &item);
    void reloadSlaves();

    QVariant dataBackground(QModelIndex const &index) const;
    QVariant dataTextColor(QModelIndex const &index) const;
};

#endif // SLAVEMODEL_H
