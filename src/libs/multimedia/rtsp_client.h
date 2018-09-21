#ifndef RTSPCLIENT_H
#define RTSPCLIENT_H

#include <QWidget>
#include <device.h>
#include "gst_element_holder.h"

class GstPipelineObserver;

class MULTIMEDIA_SHARED_EXPORT RtspClient : public Device
{
public:
    RtspClient(WId id);
    ~RtspClient() override;

public:
    void start(QVariantHash const &params) override;
    void stop() final override;

public:
    gboolean onBusMessage(GstMessage *message);
    GstBusSyncReply onBusPostMessage(GstMessage *message);

private:
    WId _id;
    GstElementHolder _src;
    GstElementHolder _decodebin;
    GstElementHolder _videosink;
    GstElementHolder _pipeline;
    guint _busWatchId{ 0 };
};

#endif // RTSPCLIENT_H
