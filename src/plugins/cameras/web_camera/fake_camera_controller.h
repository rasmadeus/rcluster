#ifndef FAKE_CAMERA_CONTROLLER_H
#define FAKE_CAMERA_CONTROLLER_H

#include <QObject>
#include <slave_controller.h>
#include <memory>
#include "rtsp_server_runner.h"

class FakeCameraController : public QObject, public SlaveController
{
    Q_OBJECT

public:
    explicit FakeCameraController();
    ~FakeCameraController() override { stop(); }

public:
    void init() override {}
    void onSetup(Slave const &slave) override;

private:
    void stop();

private:
    std::unique_ptr<RtspServerRunner> _runner;
};

#endif // FAKE_CAMERA_CONTROLLER_H
