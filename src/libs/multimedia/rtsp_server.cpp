extern "C"
{
    #include <gst/gst.h>
}

#include <QDebug>
#include <config.h>
#include "rtsp_server.h"
#include "gst_pipeline_observer.h"

namespace
{
    GstRTSPFilterResult removeAllClients ([[maybe_unused]] GstRTSPServer* server, [[maybe_unused]] GstRTSPClient* client, [[maybe_unused]] gpointer data)
    {
        return GST_RTSP_FILTER_REMOVE;
    }

    void onClientConnected([[maybe_unused]] GstRTSPServer *server, GstRTSPClient *client, [[maybe_unused]] gpointer userData)
    {
        auto const *rtspConnection = gst_rtsp_client_get_connection(client);
        qDebug() << "Client connected from:" << gst_rtsp_connection_get_ip(rtspConnection);
    }

    void onMediaNewState(GstRTSPMedia *media, gint state, gpointer userData)
    {
        qDebug() << "Media" << media << "for server" << userData << "has a new state:" << state;
    }

    void onMediaConstructed([[maybe_unused]] GstRTSPMediaFactory *factory, GstRTSPMedia *media, gpointer userData)
    {
        qDebug() << "Media" << media << "has been constructed for server" << userData;
        g_signal_connect(media, "new-state", G_CALLBACK(onMediaNewState), userData);
    }
}

QString RtspServer::launch(VideoSourceType type, QVariantHash const &params)
{
    switch(type)
    {
        case VideoSourceType::FakeCamera:
            return QStringLiteral("( videotestsrc is-live=1 ! x264enc ! rtph264pay name=pay0 pt=96 )");
        case VideoSourceType::WebCamera:
            return QStringLiteral("( ksvideosrc device-index=%1 ! videoconvert ! x264enc ! video/x-h264, profile=baseline ! rtph264pay name=pay0 pt=96 )")
                .arg(params.value(QStringLiteral("camera_index")).toInt());
        case VideoSourceType::Display:
            return QStringLiteral("(dx9screencapsrc monitor=%1 cursor=1 ! videoconvert ! x264enc ! video/x-h264, profile=baseline ! rtph264pay name=pay0 pt=96 )")
                .arg(params.value(QStringLiteral("display_index")).toInt());
		default:
			return {};
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
    return config.node(computerId).param(QStringLiteral("ip")).toString();
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
    auto const port = config.node(cameraId).param(QStringLiteral("port")).toInt();
    return url(host(config, cameraId), port, cameraId);
}

RtspServer::RtspServer(QObject *parent)
    : DefaultDevice{ parent }
{
}

RtspServer::~RtspServer()
{
    stop();
}

void RtspServer::start(QVariantHash const &params)
{
    stop();

    Q_ASSERT(_server == nullptr);

    _server = gst_rtsp_server_new();
    _factory = gst_rtsp_media_factory_new();
    _host = params.value(QStringLiteral("host")).toString();
    _port = params.value(QStringLiteral("port")).toString();
    _mountPath = QStringLiteral("/%1").arg(params.value(QStringLiteral("mount_path")).toString());
    _launch = params.value(QStringLiteral("launch")).toString();

    g_signal_connect(_server, "client-connected", G_CALLBACK(::onClientConnected), this);
    g_signal_connect(_factory, "media-constructed", G_CALLBACK(::onMediaConstructed), this);

    gst_rtsp_server_set_address(_server, _host.toUtf8().constData());
    gst_rtsp_server_set_service(_server, _port.toUtf8().constData());
    auto mounts = gst_rtsp_server_get_mount_points(_server);
    gst_rtsp_media_factory_set_launch(_factory, _launch.toUtf8().constData());
    gst_rtsp_media_factory_set_shared(_factory, TRUE);
    gst_rtsp_mount_points_add_factory (mounts, _mountPath.toUtf8().constData(), _factory);
    g_object_unref (mounts);
    _id = gst_rtsp_server_attach(_server, nullptr);

    emit stateChanged(Device::State::On);
}

void RtspServer::stop()
{
    if (_server != nullptr)
    {
        gst_rtsp_server_client_filter(_server, ::removeAllClients, nullptr);

        auto mounts = gst_rtsp_server_get_mount_points(_server);
        gst_rtsp_mount_points_remove_factory(mounts, _mountPath.toUtf8().constData());
        g_object_unref(mounts);

        auto pool = gst_rtsp_server_get_session_pool(_server);
        gst_rtsp_session_pool_cleanup(pool);
        g_object_unref(pool);

        g_source_remove(_id);
        g_object_unref(_factory);
        g_object_unref(_server);

        _factory = nullptr;
        _server = nullptr;
    }

    emit stateChanged(Device::State::Off);
}

QString RtspServer::url() const
{
    return url(_host, _port.toInt(), _mountPath);
}
