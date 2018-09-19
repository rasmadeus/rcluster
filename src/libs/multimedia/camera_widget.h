#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

extern "C"
{
    #include <gst/gst.h>
}

#include <memory>
#include <QWidget>
#include "gst_pipeline_observer.h"
#include "rtsp_client.h"
#include "multimedia_global.h"

class MULTIMEDIA_SHARED_EXPORT CameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWidget(QString const &url, QWidget &parent);

public:
    void setUrl(QString const &url);

protected:
    void paintEvent(QPaintEvent *ev) override;
    void timerEvent(QTimerEvent *ev) override;

private:
    void onError();
    void onStateChanged(int state) { _state = state; }

private:
    QString _url;
    GstPipelineObserver _observer;
    std::unique_ptr<RtspClient> _client;
    int _reconnectTimerId{ -1 };
    int _state{ GST_STATE_NULL };
};

#endif // CAMERA_WIDGET_H
