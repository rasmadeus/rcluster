#ifndef SLAVE_TYPE_PROXY_MODEL_H
#define SLAVE_TYPE_PROXY_MODEL_H

#include "slave_sort_model.h"
#include "widgets_global.h"

class WIDGETS_SHARED_EXPORT SlaveTypeProxyModel : public SlaveSortModel
{
    Q_OBJECT

public:
    explicit SlaveTypeProxyModel(QStringList const &types, QStringList const &checkableTypes, QObject &parent);

public:
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(QModelIndex const &index) const override;

protected:
    bool filterAcceptsRow(int sourceRow, QModelIndex const &sourceParent) const override;

private:
    QStringList const _types;
    QStringList const _checkableTypes;
};

#endif // SLAVE_TYPE_PROXY_MODEL_H
