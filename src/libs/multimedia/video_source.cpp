extern "C"
{
    #include <libavdevice/avdevice.h>
    #include <libavformat/avformat.h>
}

#include <QApplication>
#include <QDebug>
#include "video_source.h"

class AVFormatContextGuard
{
public:
    AVFormatContextGuard(AVFormatContextGuard const &) = delete;
    AVFormatContextGuard &operator = (AVFormatContextGuard const &) = delete;

    AVFormatContextGuard(AVFormatContext *context)
        : _context{ context }
    {
    }

    ~AVFormatContextGuard()
    {
        if (_context)
            avformat_close_input(&_context);
    }

private:
    AVFormatContext *_context;
};

class AVCodecContextGuard
{
public:
    AVCodecContextGuard(AVFormatContextGuard const &) = delete;
    AVCodecContextGuard &operator = (AVFormatContextGuard const &) = delete;

    AVCodecContextGuard(AVCodecContext *context)
        : _context{ context }
    {
    }

    ~AVCodecContextGuard()
    {
        if (_context)
            avcodec_close(_context);
    }

private:
    AVCodecContext *_context;
};

VideoSource::VideoSource(QObject *parent)
    : ActiveDevice{ parent }
{
}

void VideoSource::run(QVariantHash const &params)
{
    avdevice_register_all();

    auto const format = QStringLiteral("dshow");
    auto const deviceDesc = QStringLiteral("video=%1").arg(params.value(QStringLiteral("device_desc")).toString());

    auto formatContext = avformat_alloc_context();
    AVFormatContextGuard const formatContextGuard{ formatContext };
    if (!formatContext)
    {
        qCritical() << "Failed to create avformat_alloc_context for" << format << deviceDesc;
        return;
    }

    auto formatInput = av_find_input_format(format.toStdString().c_str());
    if (!formatInput)
    {
        qCritical() << "Failed to create av_find_input_format for" << format << deviceDesc;
        return;
    }

    if (avformat_open_input(&formatContext, deviceDesc.toStdString().c_str(), formatInput, nullptr) != 0)
    {
        qCritical() << "Failed to avformat_open_input for" << format << deviceDesc;
        return;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0)
    {
        qCritical() << "Failed to avformat_find_stream_info for" << format << deviceDesc;
        return;
    }

    int videoStream = -1;
    for(std::size_t i = 0; i < formatContext->nb_streams; ++i)
    {
        if(formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = static_cast<int>(i);
            break;
        }
    }

    if(videoStream == -1)
    {
        qCritical() << "Failed to find videoStream";
        return;
    }

    auto stream = formatContext->streams[videoStream];
    auto codec = avcodec_find_decoder(stream->codecpar->codec_id);

    if (codec == nullptr)
    {
        qCritical() << "Failed to avcodec_find_decoder for" << format << deviceDesc;
        return;
    }

    auto codecContext = stream->codec;
    AVCodecContextGuard const codecContextGuard{ codecContext };

    if (avcodec_open2(codecContext, codec, nullptr) < 0)
    {
        qCritical() << "Failed to avcodec_open2 for" << format << deviceDesc;
        return;
    }

    qDebug() << QStringLiteral("Stream info: width = %1; height = %2; framerate = %3/%4")
        .arg(codecContext->width)
        .arg(codecContext->height)
        .arg(codecContext->framerate.num)
        .arg(codecContext->framerate.den);

    AVPacket packet;

    emit started();

    while(!doStop())
    {
        if (av_read_frame(formatContext, &packet) < 0)
            break;

        emit ready();
        av_packet_unref(&packet);
    }

    emit stopped();

}
