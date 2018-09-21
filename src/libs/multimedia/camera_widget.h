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
    void onError();
    void onStateChanged(DeviceState state) { _state = state; }

private:
    QString _url;
    std::unique_ptr<RtspClient> _client;
    int _reconnectTimerId{ -1 };
    DeviceState _state{ DeviceState::Unknown };
};

#endif // CAMERA_WIDGET_H
