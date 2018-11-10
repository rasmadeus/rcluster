#ifndef EYE_TRACKER_H
#define EYE_TRACKER_H

#include "default_device.h"
#include "utils_global.h"

struct GAZE_DATA;

class UTILS_SHARED_EXPORT EyeTracker : public DefaultDevice
{
    Q_OBJECT

public:
    explicit EyeTracker(QObject *parent = nullptr);

public:
    virtual void startCalibration(int displayWidth, int displayHeight) = 0;
    virtual void stopCalibration() = 0;

signals:
    void ready(GAZE_DATA const &gazeData);
    void calibrationStateChanged(int state, int index, int x, int y, bool blink);
    void calibrationStopped(bool state, float quality);
    void calibrationFailed();
};

#endif // EYE_TRACKER_H
