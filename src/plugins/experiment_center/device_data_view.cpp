#include <config.h>
#include "device_data_view.h"

DeviceDataView::DeviceDataView(QUuid const &id, Config const &config, QWidget &parent)
    : QMdiSubWindow{ &parent }
    , _id{ id }
    , _config{ config }
{
    updateTitle();
    setAttribute(Qt::WA_DeleteOnClose);
    connect(&config, &Config::renamed, this, &DeviceDataView::onSlaveRenamed);
}

void DeviceDataView::updateTitle()
{
    setWindowTitle(_config.slave(_id).name());
}

void DeviceDataView::onSlaveRenamed(QUuid const &id)
{
    if (id == _id)
        updateTitle();
}
