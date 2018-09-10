#include <config.h>
#include <core_bus.h>
#include "camera_controller.h"
#include <QCameraInfo>

CameraController::CameraController()
    : ControllerWithoutActivity{}
{
}

void CameraController::onSetup(Slave const &slave)
{
}
