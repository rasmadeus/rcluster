extern "C"
{
    #include <gst/video/video-overlay-composition.h>
}

#include <QApplication>
#include <QDebug>
#include <device_state.h>
#include "gst_pipeline_observer.h"
#include "rtsp_client.h"

namespace
{
    void onDecodebinPadAdded(GstElement *element, GstPad *pad, gpointer data)
    {
        Q_UNUSED(element)

        qDebug() << "Pad added";
        auto decodebin = static_cast<GstElement*>(data);
        auto sinkPad = gst_element_get_static_pad(decodebin, "sink");
        if (!gst_pad_is_linked(sinkPad))
        {
            auto const ret = gst_pad_link (pad, sinkPad);
            qDebug() << "Decodebin pad linked state:" << GST_PAD_LINK_FAILED(ret);
        }
    }

    void onVideoSinkPadAdded(GstElement *element, GstPad *pad, gpointer userData)
    {
        Q_UNUSED(element)

        qDebug() << "Decoded Pad added";
        auto decodebin = static_cast<GstElement*>(userData);
        auto sinkPad = gst_element_get_static_pad (decodebin, "sink");
        if (!gst_pad_is_linked (sinkPad))
        {
            auto const ret = gst_pad_link (pad, sinkPad);
            qDebug() << "Videosink pad linked state:" << GST_PAD_LINK_FAILED(ret);
        }
    }

    GstBusSyncReply onBusPostMessage (GstBus *bus, GstMessage *message, gpointer userData)
    {
        Q_UNUSED(bus)
        return static_cast<RtspClient*>(userData)->onBusPostMessage(message);
    }

    gboolean onBusMessage(GstBus *bus, GstMessage *message, gpointer userData)
    {
        Q_UNUSED(bus)
        return static_cast<RtspClient*>(userData)->onBusMessage(message);
    }
}

RtspClient::RtspClient(WId id)
    : _id{ id }
    , _src{ "rtspsrc", "rtspsrc" }
    , _decodebin{ "decodebin", "decodebin" }
    , _videosink{ "glimagesink", "glimagesink" }
    , _pipeline{ "rtsp_client" }
{
    if (!_pipeline.get() || !_src.get() || !_decodebin.get() || !_videosink.get())
        return;

    gst_bin_add_many(GST_BIN(_pipeline.get()), _src.get(), _decodebin.get(), _videosink.get(), nullptr);

    _src.connect(QStringLiteral("pad-added"), G_CALLBACK(::onDecodebinPadAdded), _decodebin.get());
    _decodebin.connect(QStringLiteral("pad-added"), G_CALLBACK(::onVideoSinkPadAdded), _videosink.get());

    auto bus = _pipeline.bus();
    gst_bus_set_sync_handler(bus, ::onBusPostMessage, this, nullptr);
    _busWatchId = gst_bus_add_watch(bus, ::onBusMessage, this);
}

RtspClient::~RtspClient()
{
    stop();
}

void RtspClient::start(QVariantHash const &params)
{
    _src.setProperty(QStringLiteral("location"), params.value(QStringLiteral("location")).toString());
    auto const playState = _pipeline.setState(GST_STATE_PLAYING);
    qDebug() << "Play state:" << playState;
}

void RtspClient::stop()
{
    _pipeline.setState(GST_STATE_NULL);
}

gboolean RtspClient::onBusMessage(GstMessage *message)
{
    switch (GST_MESSAGE_TYPE(message))
    {
        case GST_MESSAGE_STATE_CHANGED:
        {
            GstState oldState;
            GstState newState;
            gst_message_parse_state_changed(message, &oldState, &newState, nullptr);
            emit stateChanged(newState == GST_STATE_PLAYING ? DeviceState::On : DeviceState::Off);
            break;
        }
        case GST_MESSAGE_WARNING:
        {
            GError *er;
            gchar *debug;
            gst_message_parse_warning(message, &er, &debug);
            g_error_free(er);
            g_free(debug);
            logError(er->message);
            break;
        }
        case GST_MESSAGE_ERROR:
        {
            GError *er;
            gchar *debug;
            gst_message_parse_error (message, &er, &debug);
            qDebug() << "RtpClient error:" <<  er->message;
            g_error_free(er);
            g_free(debug);
            logError(er->message);
            break;
        }
        default:
            break;
   }
   return TRUE;
}

GstBusSyncReply RtspClient::onBusPostMessage(GstMessage *message)
{
    if (!gst_is_video_overlay_prepare_window_handle_message (message))
        return GST_BUS_PASS;

    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY (GST_MESSAGE_SRC(message)), _id);
    gst_message_unref(message);
    qDebug() << "Window created for" << _id;
    return GST_BUS_DROP;
}
