#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <rtsp_server.h>
#include <gloop.h>

#include <QObject>
#include <controller_without_activity.h>
#include <memory>

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
    std::unique_ptr<Gloop> _gloop;
    std::unique_ptr<RtspServer> _server;

};

#endif // CAMERA_CONTROLLER_H
