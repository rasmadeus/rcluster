#include <QDebug>
#include "video_writer.h"

namespace
{
    gboolean onBusMessage([[maybe_unused]] GstBus *bus, GstMessage *message, gpointer userData)
    {
        return static_cast<VideoWriter*>(userData)->onBusMessage(message);
    }
}

VideoWriter::VideoWriter(QObject *parent)
    : DeviceWriter{ parent }
{
}

void VideoWriter::start(QVariantHash const &params)
{
    stop();

    auto const launch = QStringLiteral("rtspsrc location=%1 ! decodebin ! x264enc ! video/x-h264, profile=baseline ! mp4mux ! filesink location=%2")
        .arg(params.value(QStringLiteral("url")).toString())
        .arg(path());

    qDebug() << "VideoWriter launch:" << launch;

    auto element = gst_parse_launch(launch.toLocal8Bit().constData(), nullptr);
    _pipeline = std::make_unique<GstElementHolder>(QStringLiteral("launch"), element);

    _bus = _pipeline->bus();
    gst_bus_add_watch(_bus, ::onBusMessage, this);

    _pipeline->setState(GstState::GST_STATE_PLAYING);
}

void VideoWriter::stop()
{
    if (_pipeline)
        gst_element_send_event(_pipeline->get(), gst_event_new_eos());
}

gboolean VideoWriter::onBusMessage(GstMessage *message)
{
    switch (GST_MESSAGE_TYPE(message))
    {
        case GST_MESSAGE_EOS:
        {
            if (_bus)
            {
                _pipeline->setState(GstState::GST_STATE_NULL);
                g_object_unref(_bus);
                _bus = nullptr;
                _pipeline.reset();
                emit stateChanged(State::Off);
            }
            break;
        }
        case GST_MESSAGE_STATE_CHANGED:
        {
            GstState oldState;
            GstState newState;
            gst_message_parse_state_changed(message, &oldState, &newState, nullptr);
            emit stateChanged(newState == GST_STATE_PLAYING ? Device::State::On : Device::State::Off);
            break;
        }
        case GST_MESSAGE_WARNING:
        {
            GError *er;
            gchar *debug;
            gst_message_parse_warning(message, &er, &debug);
            emit error(er->message);
            qCritical() << er->message;
            g_error_free(er);
            g_free(debug);
            break;
        }
        case GST_MESSAGE_ERROR:
        {
            GError *er;
            gchar *debug;
            gst_message_parse_error(message, &er, &debug);
            emit error(er->message);
            qCritical() << er->message;
            g_error_free(er);
            g_free(debug);
            break;
        }
        default:
            break;
   }
   return TRUE;
}
