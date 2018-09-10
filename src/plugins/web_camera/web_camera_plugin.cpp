#include "web_camera_controller.h"
#include "web_camera_plugin.h"
#include "web_camera_editor.h"

Editor *WebCameraPlugin::editor(QWidget &parent) const
{
    return new WebCameraEditor{ parent };
}

std::unique_ptr<SlaveController> WebCameraPlugin::controller() const
{
    return std::make_unique<WebCameraController>();
}

QVariantHash WebCameraPlugin::defaultParams() const
{
    return {
        { QStringLiteral("type"), QVariant::fromValue(VideoSourceType::Fake) },
    };
}
