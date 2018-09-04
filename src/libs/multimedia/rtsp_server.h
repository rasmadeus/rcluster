#ifndef RTSP_SERVER_H
#define RTSP_SERVER_H

extern "C"
{
    #include <gst/gst.h>
    #include <gst/rtsp-server/rtsp-server.h>
}

#include <QString>
#include <QUuid>
#include <device.h>
#include "multimedia_global.h"

class MULTIMEDIA_SHARED_EXPORT RtspServer : public Device
{
    Q_OBJECT

public:
    static QString url(QString const &host, QString const &port, QString const &mountPath);
    static QString mountPath(QUuid const &cameraId);

public:
    explicit RtspServer(QObject *parent = nullptr);
    ~RtspServer() override;

public:
    void start(QVariantHash const &params) override;
    void stop() override;

public:
    bool isStarted() const { return !_mountPath.isEmpty(); }

private:
    void shutdown();
    void cleanupSession();

private:
    QString _mountPath;
    GstRTSPServer *_server{ nullptr };
    GstRTSPMediaFactory *_factory{ nullptr };
};

#endif // RTSP_SERVER_H
