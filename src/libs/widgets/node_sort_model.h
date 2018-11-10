#ifndef SLAVE_SORT_MODEL_H
#define SLAVE_SORT_MODEL_H

#include <QSortFilterProxyModel>
#include "widgets_global.h"

class WIDGETS_SHARED_EXPORT NodeSortModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit NodeSortModel(QObject &parent);

protected:
    bool lessThan(QModelIndex const &sourceLeft, QModelIndex const &sourceRight) const override;
};

#endif // SLAVE_SORT_MODEL_H
