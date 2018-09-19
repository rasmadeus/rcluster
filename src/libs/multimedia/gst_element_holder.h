#ifndef GST_ELEMENT_HOLDER_H
#define GST_ELEMENT_HOLDER_H

extern "C"
{
    #include <gst/gst.h>
}

#include <QString>
#include "multimedia_global.h"


class MULTIMEDIA_SHARED_EXPORT GstElementHolder
{
public:
    GstElementHolder(QString const &factoryName, QString const &name);
    GstElementHolder(QString const &pipelineName);
    ~GstElementHolder();

public:
    GstBus* bus() const { return gst_pipeline_get_bus(GST_PIPELINE(_element)); }
    GstElement *get() const { return _element; }
    void setProperty(QString const &key, QString const &value);
    GstStateChangeReturn setState(GstState state);
    void connect(QString const &signal, GCallback handler, gpointer data);

private:
    void logError();

private:
    QString const _name;
    GstElement *_element;
};

#endif // GST_ELEMENT_HOLDER_H
