extern "C"
{
    #include <gst/video/video-overlay-composition.h>
}

#include <QApplication>
#include <QDebug>
#include "gst_pipeline_observer.h"
#include "rtsp_client.h"

namespace
{
    void onDecodebinPadAdded(GstElement *element, GstPad *pad, gpointer data)
    {
        Q_UNUSED(element)

        qDebug() << "Pad added";
        GstElement *decodebin = static_cast<GstElement*>(data);
        GstPad *sinkPad = gst_element_get_static_pad(decodebin, "sink");
        if (!gst_pad_is_linked(sinkPad))
        {
            auto const ret = gst_pad_link (pad, sinkPad);
            qDebug() << "Decodebin pad linked state:" << GST_PAD_LINK_FAILED(ret);
        }
    }

    void onVideoSinkPadAdded(GstElement *element, GstPad *pad, gpointer data)
    {
        Q_UNUSED(element)

        qDebug() << "Decoded Pad added";
        GstElement *decodebin = static_cast<GstElement*>(data);
        GstPad *sinkPad = gst_element_get_static_pad (decodebin, "sink");
        if (!gst_pad_is_linked (sinkPad))
        {
            auto const ret = gst_pad_link (pad, sinkPad);
            qDebug() << "Videosink pad linked state:" << GST_PAD_LINK_FAILED(ret);
        }
    }

    GstBusSyncReply onBusPostMessage (GstBus *bus, GstMessage *message, gpointer userData)
    {
        Q_UNUSED(bus)

        if (!gst_is_video_overlay_prepare_window_handle_message (message))
            return GST_BUS_PASS;

        static_cast<RtspClient*>(userData)->createWindow(message);
        return GST_BUS_DROP;
    }

    gboolean onBusMessage(GstBus *bus, GstMessage *message, gpointer userData)
    {
        Q_UNUSED(bus)

        switch (GST_MESSAGE_TYPE(message))
        {
            case GST_MESSAGE_STATE_CHANGED:
            {
                GstState oldState;
                GstState newState;
                gst_message_parse_state_changed(message, &oldState, &newState, nullptr);
                static_cast<RtspClient*>(userData)->emitStateChanged(newState);
                break;
            }
            case GST_MESSAGE_WARNING:
            {
                GError *er;
                gchar *debug;
                gst_message_parse_warning(message, &er, &debug);
                qDebug() << "RtpClient warning:" <<  er->message;
                g_error_free(er);
                g_free(debug);
                static_cast<RtspClient*>(userData)->emitError();
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
                static_cast<RtspClient*>(userData)->emitError();
                break;
            }
            case GST_MESSAGE_EOS:
            {
              qDebug() << "End of stream";
              break;
            }
            default:
                break;
       }
       return TRUE;
    }
}

RtspClient::RtspClient(QString const &url, WId id, GstPipelineObserver &observer)
    : _id{ id }
    , _observer{ observer}
    , _src{ "rtspsrc", "rtspsrc" }
    , _decodebin{ "decodebin", "decodebin" }
    , _videosink{ "glimagesink", "glimagesink" }
    , _pipeline{ "rtsp_client" }
{
    if (!_pipeline.get() || !_src.get() || !_decodebin.get() || !_videosink.get())
        return;

    gst_bin_add_many(GST_BIN(_pipeline.get()), _src.get(), _decodebin.get(), _videosink.get(), nullptr);

    _src.setProperty(QStringLiteral("location"), url);
    _src.connect(QStringLiteral("pad-added"), G_CALLBACK(::onDecodebinPadAdded), _decodebin.get());
    _decodebin.connect(QStringLiteral("pad-added"), G_CALLBACK(::onVideoSinkPadAdded), _videosink.get());

    auto bus = _pipeline.bus();
    gst_bus_set_sync_handler(bus, ::onBusPostMessage, this, nullptr);
    _busWatchId = gst_bus_add_watch(bus, ::onBusMessage, this);

    play();
}

RtspClient::~RtspClient()
{
    _pipeline.setState(GST_STATE_NULL);
}

void RtspClient::play()
{
    auto const playState = _pipeline.setState(GST_STATE_PLAYING);
    qDebug() << "Play state:" << playState;
}

void RtspClient::createWindow(GstMessage *message)
{
    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (GST_MESSAGE_SRC(message)), _id);
    gst_message_unref (message);
    qDebug() << "Window created for" << _id;
}

void RtspClient::emitError()
{
    _observer.onError();
}

void RtspClient::emitStateChanged(int state)
{
    _observer.onStateChanged(state);
}
