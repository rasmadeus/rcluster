#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <QObject>
#include <slave_controller.h>
#include <memory>
#include "rtsp_server_runner.h"

class CameraController : public QObject, public SlaveController
{
    Q_OBJECT

public:
    explicit CameraController();
    ~CameraController() override { stop(); }

public:
    void init() override {}
    void onSetup(Slave const &slave) override;

private:
    void stop();

private:
    std::unique_ptr<RtspServerRunner> _runner;
};

#endif // CAMERA_CONTROLLER_H
