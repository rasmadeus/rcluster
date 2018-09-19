#include <QDebug>
#include "gst_element_holder.h"

GstElementHolder::GstElementHolder(QString const &factoryName, QString const &name)
    : _name{ factoryName }
    , _element{ gst_element_factory_make(factoryName.toUtf8().constData(), name.toUtf8().constData()) }
{
    logError();
}

GstElementHolder::GstElementHolder(QString const &pipelineName)
    : _name{ pipelineName }
    , _element{ gst_pipeline_new(pipelineName.toUtf8().constData()) }
{
    logError();
}

GstElementHolder::~GstElementHolder()
{
    if (_element)
        gst_object_unref(_element);
}

void GstElementHolder::logError()
{
    if (!_element)
        qCritical() << "Failed to create object" << _name;
}

void GstElementHolder::setProperty(QString const &key, QString const &value)
{
    if (_element)
        g_object_set(_element, key.toUtf8().constBegin(), value.toUtf8().constData(), nullptr);
}

GstStateChangeReturn GstElementHolder::setState(GstState state)
{
    return _element ? gst_element_set_state (_element, state) : GST_STATE_CHANGE_FAILURE;
}

void GstElementHolder::connect(QString const &signal, GCallback handler, gpointer data)
{
    if (_element)
        g_signal_connect(_element, signal.toUtf8().constData(), handler, data);
}
