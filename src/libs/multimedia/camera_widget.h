#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include <QWidget>
#include <rtsp_client.h>
#include "multimedia_global.h"

class MULTIMEDIA_SHARED_EXPORT CameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWidget(QString const &url, QWidget &parent);

private:
    RtspClient _client;
};

#endif // CAMERA_WIDGET_H
