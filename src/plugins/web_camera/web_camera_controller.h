#ifndef WEB_CAMERA_CONTROLLER_H
#define WEB_CAMERA_CONTROLLER_H

#include <controller_without_activity.h>

class WebCameraController : public ControllerWithoutActivity
{
    Q_OBJECT

public:
    explicit WebCameraController();

public:
    void onSetup(Slave const &slave) override;
};

#endif // WEB_CAMERA_CONTROLLER_H
