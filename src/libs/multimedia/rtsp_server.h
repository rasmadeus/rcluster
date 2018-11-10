#ifndef RTSP_SERVER_H
#define RTSP_SERVER_H

extern "C"
{
    #include <gst/rtsp-server/rtsp-server.h>
}

#include <default_device.h>
#include <QVariantHash>
#include <QString>
#include <QUuid>
#include "multimedia_global.h"
#include "video_source_type.h"

class Config;
class GstPipelineObserver;

class MULTIMEDIA_SHARED_EXPORT RtspServer : public DefaultDevice
{
    Q_OBJECT

public:
    static QString launch(VideoSourceType type, QVariantHash const &params);
    static QString toMountPath(QUuid const &id);
    static QString host(Config const &config, QUuid const &cameraId);
    static QString url(QString const &host, int port, QString const &mountPath);
    static QString url(QString const &host, int port, QUuid const &cameraId);
    static QString url(Config const &config, QUuid const &cameraId);

public:
    explicit RtspServer(QObject *parent = nullptr);
    ~RtspServer() override;

public:
    void start(QVariantHash const &params) override;
    void stop() final override;

    QString url() const;

private:
    GstRTSPServer *_server{ nullptr };
    GstRTSPMediaFactory *_factory{ nullptr };

private:
    QString _host;
    QString _port;
    QString _mountPath;
    QString _launch;
    guint _id;
};

#endif // RTSP_SERVER_H
