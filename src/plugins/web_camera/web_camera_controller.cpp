#include <config.h>
#include <core_bus.h>
#include "web_camera_controller.h"
#include <QCameraInfo>
#include <video_source.h>

WebCameraController::WebCameraController()
    : ControllerWithoutActivity{}
{
}

void WebCameraController::onSetup(Slave const &slave)
{
}
