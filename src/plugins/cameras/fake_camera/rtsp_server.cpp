#include <QDebug>
#include <QTimerEvent>
#include "rtsp_server.h"

namespace
{
    GstRTSPFilterResult clientFilter(GstRTSPServer *server, GstRTSPClient *client, gpointer userData)
    {
        Q_UNUSED(server)
        Q_UNUSED(client)
        Q_UNUSED(userData)
        return GST_RTSP_FILTER_REMOVE;
    }
}

RtspServer::RtspServer(QString const &host, QString const &mountPath, QString const &launch)
    : _mountPath{ mountPath }
    , _server{ gst_rtsp_server_new() }
    , _factory{ gst_rtsp_media_factory_new () }
{
    gst_rtsp_server_set_address(_server, host.toUtf8().constData());
    gst_rtsp_media_factory_set_shared (_factory, TRUE);

    auto mounts = gst_rtsp_server_get_mount_points(_server);
    gst_rtsp_media_factory_set_launch (_factory, launch.toUtf8().constData());
    gst_rtsp_mount_points_add_factory (mounts, mountPath.toUtf8().constData(), _factory);
    g_object_unref (mounts);

    if (gst_rtsp_server_attach (_server, nullptr))
        qDebug() << "RTSP server was attached at" << host << mountPath << launch;
    else
        qCritical() << "Failed to attach RTSP server at" << host << mountPath << launch;
}

RtspServer::~RtspServer()
{
    Q_ASSERT(_mountPath.isEmpty());
}

void RtspServer::stop()
{
    cleanupSession();
    shutdown();
}

void RtspServer::shutdown()
{
    auto mounts = gst_rtsp_server_get_mount_points(_server);
    gst_rtsp_mount_points_remove_factory(mounts, _mountPath.toUtf8().constData());
    g_object_unref(mounts);
    gst_rtsp_server_client_filter(_server, ::clientFilter, nullptr);
}

void RtspServer::cleanupSession()
{
    auto pool = gst_rtsp_server_get_session_pool(_server);
    gst_rtsp_session_pool_cleanup(pool);
    g_object_unref(pool);
    _mountPath.clear();
}
