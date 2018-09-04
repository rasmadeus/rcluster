extern "C"
{
    #include <gst/gst.h>
}

#include <config.h>
#include <core_bus.h>
#include "camera_controller.h"

CameraController::CameraController()
    : ControllerWithoutActivity{}
{
    gst_init(nullptr, nullptr);
    _gloop = std::make_unique<Gloop>();
    _server = std::make_unique<RtspServer>();
}

CameraController::~CameraController()
{
    stop();
}

void CameraController::onSetup(Slave const &slave)
{
    stop();
    start(slave);
}

void CameraController::stop()
{
    if (_server->isStarted())
        _server->stop();
}

void CameraController::start(Slave const &slave)
{
    _server->start(slave.params());
}
