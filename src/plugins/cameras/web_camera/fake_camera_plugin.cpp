#include "fake_camera_controller.h"
#include "fake_camera_plugin.h"
#include "fake_camera_editor.h"

Editor *FakeCameraPlugin::editor(QWidget &parent) const
{
    return new FakeCameraEditor{ parent };
}

std::unique_ptr<SlaveController> FakeCameraPlugin::controller() const
{
    return std::make_unique<FakeCameraController>();
}
