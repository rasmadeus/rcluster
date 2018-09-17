#ifndef RTSP_SERVER_OBSERVER_H
#define RTSP_SERVER_OBSERVER_H

#include <QObject>
#include "multimedia_global.h"

class MULTIMEDIA_SHARED_EXPORT RtspServerObserver : public QObject
{
    Q_OBJECT

public:
    explicit RtspServerObserver(QObject *parent = nullptr);

public:
    void onStateChanged(int state) { emit stateChanged(state); }

signals:
    void stateChanged(int state);
};

#endif // RTSP_SERVER_OBSERVER_H
