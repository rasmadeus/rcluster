#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <controller_without_activity.h>

class CameraController : public ControllerWithoutActivity
{
    Q_OBJECT

public:
    explicit CameraController();

public:
    void onSetup(Slave const &slave) override;
};

#endif // CAMERA_CONTROLLER_H
