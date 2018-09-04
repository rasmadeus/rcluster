#include <QDebug>
#include "rtsp_server.h"

namespace
{
    GstRTSPFilterResult allClientsFilter(GstRTSPServer *server, GstRTSPClient *client, gpointer userData)
    {
        Q_UNUSED(server)
        Q_UNUSED(client)
        Q_UNUSED(userData)
        return GST_RTSP_FILTER_REMOVE;
    }

    void onClientConnected(GstRTSPServer *server, GstRTSPClient *client)
    {
        Q_UNUSED(server)

        auto connection = gst_rtsp_client_get_connection(client);
        auto const *url = gst_rtsp_connection_get_url(connection);
        auto const *uri = gst_rtsp_url_get_request_uri(url);
        qDebug() << "New connection to rtsp server from:" << uri;
    }
}

QString RtspServer::url(QString const &host, QString const &port, QString const &mountPath)
{
    return QStringLiteral("rtsp://%1:%2%3").arg(host).arg(port).arg(mountPath);
}

QString RtspServer::mountPath(QUuid const &cameraId)
{
    auto res = cameraId.toString();
    res.replace('{', QString{});
    res.replace('}', QString{});
    res.prepend('/');
    return res;
}

RtspServer::RtspServer(QObject *parent)
    : Device{ parent }
    , _server{ gst_rtsp_server_new() }
    , _factory{ gst_rtsp_media_factory_new () }
{
}

RtspServer::~RtspServer()
{
    if (!_mountPath.isEmpty())
        stop();

    g_object_unref(_server);
    g_object_unref(_factory);
}

void RtspServer::start(QVariantHash const &params)
{
    Q_ASSERT(!isStarted());

    auto const host = params.value(QStringLiteral("host")).toString();

    if (host.isEmpty())
        return;

    auto const port = params.value(QStringLiteral("port")).toString();
    auto const launch = params.value(QStringLiteral("launch")).toString();
    _mountPath = params.value(QStringLiteral("mount_path")).toString();

    gst_rtsp_server_set_address(_server, host.toUtf8().constData());
    gst_rtsp_server_set_service(_server, port.toUtf8().constData());
    gst_rtsp_media_factory_set_shared(_factory, TRUE);

    auto mounts = gst_rtsp_server_get_mount_points(_server);
    gst_rtsp_media_factory_set_launch (_factory, launch.toUtf8().constData());
    gst_rtsp_mount_points_add_factory (mounts, _mountPath.toUtf8().constData(), _factory);
    g_object_unref (mounts);

    if (gst_rtsp_server_attach (_server, nullptr))
    {
        qDebug() << "RTSP server was attached at" << url(host, port, _mountPath) << "as" << launch;
        g_signal_connect(_server, "client-connected", G_CALLBACK(::onClientConnected), nullptr);
    }
    else
    {
        qCritical() << "Failed to attach RTSP server at" << url(host, port, _mountPath) << "as" << launch;
        return;
    }


}

void RtspServer::stop()
{
    Q_ASSERT(isStarted());

    cleanupSession();
    shutdown();
}

void RtspServer::shutdown()
{
    auto mounts = gst_rtsp_server_get_mount_points(_server);
    gst_rtsp_mount_points_remove_factory(mounts, _mountPath.toUtf8().constData());
    g_object_unref(mounts);
    gst_rtsp_server_client_filter(_server, ::allClientsFilter, nullptr);
}

void RtspServer::cleanupSession()
{
    auto pool = gst_rtsp_server_get_session_pool(_server);
    gst_rtsp_session_pool_cleanup(pool);
    g_object_unref(pool);
    _mountPath.clear();
}
