#include <QMdiSubWindow>
#include <config.h>
#include <rtsp_client.h>
#include <rtsp_server.h>
#include <camera_widget.h>
#include "device_data_view.h"

DeviceDataView::DeviceDataView(Config const &config, QWidget &parent)
    : QMdiArea{ &parent }
    , _config{ config }
{
}

void DeviceDataView::appendView(QUuid const &id, QString const &type)
{
    auto subWindow = new QMdiSubWindow{ this };
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWidget(make(id, type, *subWindow));
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
