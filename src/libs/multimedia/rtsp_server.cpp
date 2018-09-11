extern "C"
{
    #include <gst/gst.h>
}

#include <QDebug>
#include <config.h>
#include "rtsp_server.h"

namespace
{
    GstRTSPFilterResult allClientFilter (GstRTSPServer* server, GstRTSPClient* client, gpointer data)
    {
        Q_UNUSED(server)
        Q_UNUSED(client)
        Q_UNUSED(data)
        return GST_RTSP_FILTER_REMOVE;
    }
}

QString RtspServer::launch(VideoSourceType type, QVariantHash const &params)
{
    switch(type)
    {
        case VideoSourceType::Fake: return QStringLiteral("( videotestsrc is-live=1 ! x264enc ! rtph264pay name=pay0 pt=96 )");
        case VideoSourceType::WebCamera: return QStringLiteral("( videotestsrc is-live=1 ! x264enc ! rtph264pay name=pay0 pt=96 )");
    }
}

QString RtspServer::toMountPath(QUuid const &id)
{
    auto res = id.toString();
    res.remove('{');
    res.remove('}');
    return res;
}

QString RtspServer::host(Config const &config, QUuid const &cameraId)
{
    auto const computerId = config.parent(cameraId, QStringLiteral("COMPUTER"));
    return config.slave(computerId).param(QStringLiteral("ip")).toString();
}

QString RtspServer::url(QString const &host, int port, QString const &mountPath)
{
    return QStringLiteral("rtsp://%1:%2/%3").arg(host).arg(port).arg(mountPath);
}

QString RtspServer::url(QString const &host, int port, QUuid const &cameraId)
{
    return url(host, port, toMountPath(cameraId));
}

QString RtspServer::url(Config const &config, QUuid const &cameraId)
{
    auto const port = config.slave(cameraId).param(QStringLiteral("port")).toInt();
    return url(host(config, cameraId), port, cameraId);
}

RtspServer::RtspServer(QVariantHash const &params)
    : _server{ gst_rtsp_server_new() }
    , _factory{ gst_rtsp_media_factory_new() }
    , _host{ params.value(QStringLiteral("host")).toString() }
    , _port{ params.value(QStringLiteral("port")).toString() }
    , _mountPath{ QStringLiteral("/%1").arg(params.value(QStringLiteral("mount_path")).toString()) }
    , _launch{ params.value(QStringLiteral("launch")).toString() }
{
    gst_rtsp_server_set_address(_server, _host.toUtf8().constData());
    gst_rtsp_server_set_service(_server, _port.toUtf8().constData());
    auto mounts = gst_rtsp_server_get_mount_points(_server);
    gst_rtsp_media_factory_set_launch(_factory, _launch.toUtf8().constData());
    gst_rtsp_media_factory_set_shared(_factory, TRUE);
    gst_rtsp_mount_points_add_factory (mounts, _mountPath.toUtf8().constData(), _factory);
    g_object_unref (mounts);
    gst_rtsp_server_attach(_server, nullptr);

    qDebug() << "Rtsp server started as" << _launch.toUtf8().constData() << "at" << url(_host, _port.toInt(), _mountPath);
}

RtspServer::~RtspServer()
{
    auto pool = gst_rtsp_server_get_session_pool(_server);
    gst_rtsp_session_pool_cleanup(pool);
    g_object_unref(pool);

    auto mounts = gst_rtsp_server_get_mount_points(_server);
    gst_rtsp_mount_points_remove_factory(mounts, _mountPath.toUtf8().constData());
    g_object_unref (mounts);
    gst_rtsp_server_client_filter(_server, ::allClientFilter, nullptr);

    g_object_unref(_factory);
    g_object_unref(_server);

    qDebug() << "Rtsp server stopped";
}

QString RtspServer::url() const
{
    return url(_host, _port.toInt(), _mountPath);
}