extern "C"
{
    #include <gst/gst.h>
}

#include <config.h>
#include <core_bus.h>
#include "camera_controller.h"

CameraController::CameraController()
    : QObject{}
    , SlaveController{}
{
    gst_init(nullptr, nullptr);
}

void CameraController::onSetup(Slave const &slave)
{
    Q_UNUSED(slave)
}
