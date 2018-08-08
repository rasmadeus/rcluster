#ifndef SLAVE_PROXY_CHECK_MODEL_H
#define SLAVE_PROXY_CHECK_MODEL_H

#include <QUuid>
#include "slave_sort_model.h"

class WIDGETS_SHARED_EXPORT SlaveProxyCheckModel : public SlaveSortModel
{
    Q_OBJECT

public:
    explicit SlaveProxyCheckModel(QObject &parent);

public:
    void setSlaveId(QUuid const &id);

protected:
    bool filterAcceptsRow(int sourceRow, QModelIndex const &sourceParent) const override;

private:
    QUuid _id;
};

#endif // SLAVE_PROXY_CHECK_MODEL_H
