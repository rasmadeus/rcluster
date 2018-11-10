#ifndef RTSP_RENDERER_H
#define RTSP_RENDERER_H

#include "gst_element_holder.h"
#include <QWidget>
#include <default_device.h>

class GstPipelineObserver;

class MULTIMEDIA_SHARED_EXPORT RtspRenderer : public DefaultDevice
{
public:
    RtspRenderer(WId id);
    ~RtspRenderer() override;

public:
    void start(QVariantHash const &params) override;
    void stop() final override;

public:
    gboolean onBusMessage(GstMessage *message);
    GstBusSyncReply onBusPostMessage(GstMessage *message);

private:
    WId _id;
    GstBus *_bus{ nullptr };
    GstElementHolder _src;
    GstElementHolder _decodebin;
    GstElementHolder _videosink;
    GstElementHolder _pipeline;
    guint _busWatchId{ 0 };
};

#endif // RTSP_RENDERER_H
