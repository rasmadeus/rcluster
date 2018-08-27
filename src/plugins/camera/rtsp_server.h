#ifndef RTSP_SERVER_H
#define RTSP_SERVER_H

extern "C"
{
    #include <gst/gst.h>
}

#include <atomic>
#include <QObject>

struct GstRTSPServer;
struct GstRTSPMediaFactory;

class RtspServer : public QObject
{
    Q_OBJECT

public:
    explicit RtspServer(QString const &pipeline, QString const &url, QObject *parent = nullptr);

public:
    void start();
    void stop() { _stop = true; }

private:
    gboolean checkExit(GstRTSPServer *server);




private:
    QString const _pipeline;
    QString const _url;

    std::atomic<bool> _stop{ false };

    GMainLoop *_loop;
    GstRTSPServer *_server;
    GstRTSPMediaFactory *_factory{ nullptr };
};

#endif // RTSP_SERVER_H
