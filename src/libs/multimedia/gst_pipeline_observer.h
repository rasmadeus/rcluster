#ifndef GST_PIPELINE_OBSERVER_H
#define GST_PIPELINE_OBSERVER_H

#include <QObject>
#include "multimedia_global.h"

class MULTIMEDIA_SHARED_EXPORT GstPipelineObserver : public QObject
{
    Q_OBJECT

public:
    explicit GstPipelineObserver(QObject *parent = nullptr);

public:
    void onError() { emit error(); }
    void onStateChanged(int state) { emit stateChanged(state); }

signals:
    void error();
    void stateChanged(int state);
};

#endif // RTSP_SERVER_OBSERVER_H
