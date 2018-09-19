#include <QEvent>
#include <QMdiSubWindow>
#include <config.h>
#include <plugins.h>
#include <rtsp_client.h>
#include <rtsp_server.h>
#include <camera_widget.h>
#include "device_data_view.h"
#include "devices_data_view.h"

DevicesDataView::DevicesDataView(Config const &config, Plugins const &plugins, QWidget &parent)
    : QMdiArea{ &parent }
    , _config{ config }
    , _plugins{ plugins }
{
}

void DevicesDataView::onSetup(Slave const &slave)
{
    QVariantList actualDevices;
    for(auto const &place : slave.param(QStringLiteral("respondent_places")).toList())
        for(auto const &device : _config.slave(place.toUuid()).param(QStringLiteral("devices")).toList())
            actualDevices << device.toUuid();

    for(auto deviceView : subWindowList())
        if (!actualDevices.contains(static_cast<DeviceDataView*>(deviceView)->id()))
            deviceView->close();

    tileSubWindows();
}

void DevicesDataView::appendView(QUuid const &id, QString const &type)
{
    auto subWindow = new DeviceDataView{ id, _config, *this };
    subWindow->setWidget(make(id, type, *subWindow));
    subWindow->setWindowIcon(_plugins.plugin(type)->pixmap());
    addSubWindow(subWindow);
    subWindow->show();
    tileSubWindows();
}

QWidget *DevicesDataView::make(QUuid const &id, QString const &type, QWidget &parent) const
{
    if (type == QStringLiteral("CAMERA"))
        return new CameraWidget{ RtspServer::url(_config, id), parent };
    else
        Q_ASSERT(false);
}
