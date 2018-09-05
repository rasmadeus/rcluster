#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <controller_without_activity.h>
#include <video_source.h>

class CameraController : public ControllerWithoutActivity
{
    Q_OBJECT

public:
    explicit CameraController();

public:
    void onSetup(Slave const &slave) override;

private:
    void onCamStarted();
    void onCamStopped();
    void onCamReady();

signals:
    void started(QVariantHash const &params);

private:
    VideoSource _videoSource;
};

#endif // CAMERA_CONTROLLER_H
