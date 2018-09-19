#ifndef RTSPCLIENT_H
#define RTSPCLIENT_H

#include <QWidget>
#include "gst_element_holder.h"

class GstPipelineObserver;

class MULTIMEDIA_SHARED_EXPORT RtspClient
{
public:
    RtspClient(QString const &url, WId id, GstPipelineObserver &observer);
    ~RtspClient();

public:
    void play();
    void createWindow(GstMessage *message);
    void emitError();
    void emitStateChanged(int state);

private:
    WId _id;
    GstPipelineObserver &_observer;
    GstElementHolder _src;
    GstElementHolder _decodebin;
    GstElementHolder _videosink;
    GstElementHolder _pipeline;
    guint _busWatchId{ 0 };
};

#endif // RTSPCLIENT_H
