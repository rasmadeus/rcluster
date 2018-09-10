#include "camera_controller.h"
#include "camera_plugin.h"
#include "camera_editor.h"
#include "video_source_type.h"

Editor *CameraPlugin::editor(EditorData const &data, QWidget &parent) const
{
    return new CameraEditor{ data, parent };
}

std::unique_ptr<SlaveController> CameraPlugin::controller() const
{
    return std::make_unique<CameraController>();
}

QVariantHash CameraPlugin::defaultParams() const
{
    return {
        { QStringLiteral("type"), QVariant::fromValue(VideoSourceType::Fake) },
        { QStringLiteral("port"), 5000 },
    };
}
