#include <QMdiSubWindow>
#include <config.h>
#include <plugins.h>
#include <rtsp_client.h>
#include <rtsp_server.h>
#include <camera_widget.h>
#include "device_data_view.h"

DeviceDataView::DeviceDataView(Config const &config, Plugins const &plugins, QWidget &parent)
    : QMdiArea{ &parent }
    , _config{ config }
    , _plugins{ plugins }
{
}

void DeviceDataView::appendView(QUuid const &id, QString const &type)
{
    auto subWindow = new QMdiSubWindow{ this };
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWidget(make(id, type, *subWindow));
    subWindow->setWindowIcon(_plugins.plugin(type)->pixmap());
    subWindow->setWindowTitle(_config.slave(id).name());
    addSubWindow(subWindow);
    subWindow->show();
    tileSubWindows();
}

QWidget *DeviceDataView::make(QUuid const &id, QString const &type, QWidget &parent) const
{
    if (type == QStringLiteral("CAMERA"))
        return new CameraWidget{ RtspServer::url(_config, id), parent };
    else
        Q_ASSERT(false);
}
