extern "C"
{
    #include <gst/rtsp-server/rtsp-server.h>
}

#include <functional>
#include "rtsp_server.h"

RtspServer::RtspServer(QString const &pipeline, QString const &url, QObject *parent)
    : QObject{ parent }
    , _pipeline{ pipeline }
    , _url{ url }
    , _loop{ g_main_loop_new(nullptr, gboolean{ 0 }) }
    , _server{ gst_rtsp_server_new() }
{
}

void RtspServer::start()
{
    Q_ASSERT(_factory == nullptr);

    auto mounts = gst_rtsp_server_get_mount_points(_server);
    _factory = gst_rtsp_media_factory_new();
    gst_rtsp_media_factory_set_launch(_factory, _pipeline.toStdString().c_str());
    gst_rtsp_media_factory_set_shared(_factory, gboolean{ 1 });
    gst_rtsp_mount_points_add_factory(mounts, _url.toStdString().c_str(), _factory);
    g_object_unref(mounts);

    gst_rtsp_server_attach(_server, nullptr);
    g_timeout_add_seconds(2, std::bind(&RtspServer::checkExit, this, std::placeholoders::_1), _server);
    g_main_loop_run(_loop);
}

gboolean RtspServer::checkExit(GstRTSPServer *server)
{
    if (!_stop)
        return gboolean{ 0 };

    auto mounts = gst_rtsp_server_get_mount_points (server);
    gst_rtsp_mount_points_remove_factory (mounts, _url.toStdString().c_str());
    g_object_unref (mounts);
    gst_rtsp_server_client_filter(server, clientFilter, nullptr);

    return gboolean{ 1 };
}
