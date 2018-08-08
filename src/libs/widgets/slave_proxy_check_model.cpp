#include "slave_model.h"
#include "slave_proxy_check_model.h"

SlaveProxyCheckModel::SlaveProxyCheckModel(QObject &parent)
    : SlaveSortModel{ parent }
{
}

void SlaveProxyCheckModel::setSlaveId(QUuid const &id)
{
    _id = id;
    invalidate();
}

bool SlaveProxyCheckModel::filterAcceptsRow(int sourceRow, QModelIndex const &sourceParent) const
{
    auto const id = sourceParent.child(sourceRow, SlaveModel::ColumnCaption).data(SlaveModel::RoleItemId);
    return id != _id;
}
