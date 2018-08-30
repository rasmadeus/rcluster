#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <QObject>
#include <controller_without_activity.h>
#include <memory>
#include "rtsp_server_runner.h"

class CameraController : public ControllerWithoutActivity
{
    Q_OBJECT

public:
    explicit CameraController();
    ~CameraController() override;

public:
    void onSetup(Slave const &slave) override;

private:
    void stop();
    void start(Slave const &slave);

private:
    std::unique_ptr<RtspServerRunner> _runner;
};

#endif // CAMERA_CONTROLLER_H
