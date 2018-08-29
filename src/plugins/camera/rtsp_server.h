#ifndef RTSP_SERVER_H
#define RTSP_SERVER_H

extern "C"
{
    #include <gst/gst.h>
    #include <gst/rtsp-server/rtsp-server.h>
}

#include <QString>

class RtspServer
{
public:
    explicit RtspServer(QString const &host, QString const &mountPath, QString const &launch);
    ~RtspServer();

public:
    void stop();

private:
    void shutdown();
    void cleanupSession();

private:
    QString _mountPath;
    GstRTSPServer *_server;
    GstRTSPMediaFactory *_factory;
};

#endif // RTSP_SERVER_H
