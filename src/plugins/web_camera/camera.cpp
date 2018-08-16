
#include <QDebug>
#include "camera.h"

Camera::Camera(const QString &deviceName)
    : QObject{}
{
    qDebug() << "Camera create at" << deviceName;

    avdevice_register_all();
    avcodec_register_all();

    const char  *filenameSrc = deviceName.toStdString().c_str();

    AVCodecContext  *pCodecCtx;
    AVFormatContext *pFormatCtx = avformat_alloc_context();
    AVCodec * pCodec;
    AVInputFormat *iformat = av_find_input_format("dshow");
    AVFrame *pFrame, *pFrameRGB;



    if(avformat_open_input(&pFormatCtx,filenameSrc,iformat,NULL) != 0) return ;
    if(avformat_find_stream_info(pFormatCtx, nullptr) < 0)   return ;
    av_dump_format(pFormatCtx, 0, filenameSrc, 0);
    int videoStream = 1;
    for(int i=0; i < pFormatCtx->nb_streams; i++)
    {
        if(pFormatCtx->streams[i]->codec->coder_type==AVMEDIA_TYPE_VIDEO)
        {
            videoStream = i;
            break;
        }
    }

    if(videoStream == -1) return ;
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;

    pCodec =avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodec==NULL) return; //codec not found

    if(avcodec_open2(pCodecCtx,pCodec,NULL) < 0) return;

    pFrame    = av_frame_alloc();
    pFrameRGB = av_frame_alloc();

    uint8_t *buffer;
    int numBytes;

    AVPixelFormat  pFormat = AV_PIX_FMT_BGR24;
    numBytes = avpicture_get_size(pFormat,pCodecCtx->width,pCodecCtx->height) ;
    buffer = (uint8_t *) av_malloc(numBytes*sizeof(uint8_t));
    avpicture_fill((AVPicture *) pFrameRGB,buffer,pFormat,pCodecCtx->width,pCodecCtx->height);

    int res;
    int frameFinished;
    AVPacket packet;
    while(res = av_read_frame(pFormatCtx,&packet)>=0)
    {
        qDebug() << "New frame";
    }

    av_free_packet(&packet);
    avcodec_close(pCodecCtx);
    av_free(pFrame);
    av_free(pFrameRGB);
    avformat_close_input(&pFormatCtx);
}
