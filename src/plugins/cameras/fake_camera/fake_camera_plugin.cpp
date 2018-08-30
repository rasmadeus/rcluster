#include "fake_camera_controller.h"
#include "fake_camera_plugin.h"

std::unique_ptr<SlaveController> FakeCameraPlugin::controller() const
{
    return std::make_unique<FakeCameraController>();
}
