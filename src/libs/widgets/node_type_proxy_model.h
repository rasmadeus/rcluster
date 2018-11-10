#ifndef SLAVE_TYPE_PROXY_MODEL_H
#define SLAVE_TYPE_PROXY_MODEL_H

#include "node_sort_model.h"
#include "widgets_global.h"

class WIDGETS_SHARED_EXPORT NodeTypeProxyModel : public NodeSortModel
{
    Q_OBJECT

public:
    explicit NodeTypeProxyModel(QStringList const &types, QStringList const &checkableTypes, QObject &parent);

public:
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(QModelIndex const &index) const override;
    bool setData(QModelIndex const &index, QVariant const &value, int role = Qt::EditRole) override;

protected:
    bool filterAcceptsRow(int sourceRow, QModelIndex const &sourceParent) const override;

private:
    QStringList const _types;
    QStringList const _checkableTypes;
};

#endif // SLAVE_TYPE_PROXY_MODEL_H
