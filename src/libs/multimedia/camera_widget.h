#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

extern "C"
{
    #include <gst/gst.h>
}

#include <memory>
#include <QWidget>
#include <device_state.h>
#include "rtsp_client.h"
#include "multimedia_global.h"

class MULTIMEDIA_SHARED_EXPORT CameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWidget(QWidget &parent);

public:
    void setUrl(QString const &url);

protected:
    void paintEvent(QPaintEvent *ev) override;
    void timerEvent(QTimerEvent *ev) override;

private:
    void onStateChanged(DeviceState state) { _state = state; }
    void onError();

private:
    QString _url;
    DeviceState _state{ DeviceState::Unknown };
    RtspClient _client;
    int _reconnectTimerId{ -1 };
};

#endif // CAMERA_WIDGET_H
