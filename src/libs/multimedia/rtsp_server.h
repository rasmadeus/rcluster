#ifndef RTSP_SERVER_H
#define RTSP_SERVER_H

extern "C"
{
    #include <gst/rtsp-server/rtsp-server.h>
}

#include <QVariantHash>
#include <QString>
#include <QUuid>
#include "multimedia_global.h"
#include "video_source_type.h"

class Config;
class RtspServerObserver;

class MULTIMEDIA_SHARED_EXPORT RtspServer
{
public:
    static QString launch(VideoSourceType type, QVariantHash const &params);
    static QString toMountPath(QUuid const &id);
    static QString host(Config const &config, QUuid const &cameraId);
    static QString url(QString const &host, int port, QString const &mountPath);
    static QString url(QString const &host, int port, QUuid const &cameraId);
    static QString url(Config const &config, QUuid const &cameraId);

public:
    RtspServer(RtspServerObserver &observer, QVariantHash const &params);
    ~RtspServer();

public:
    QString url() const;
    void onStateChanged(gint state);

private:
    RtspServerObserver &_observer;
    GstRTSPServer *_server;
    GstRTSPMediaFactory *_factory;

private:
    QString _host;
    QString _port;
    QString _mountPath;
    QString _launch;
};

#endif // RTSP_SERVER_H
