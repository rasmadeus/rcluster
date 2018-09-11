extern "C"
{
    #include <gst/gst.h>
}

#include <config.h>
#include <core_bus.h>
#include <video_source_type.h>
#include "camera_controller.h"

CameraController::CameraController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithoutActivity{ config, plugin, corebus }
{
    gst_init(nullptr, nullptr);
    _gloop = std::make_unique<Gloop>();
}

CameraController::~CameraController()
{
    _rtspServer.reset();
    _gloop.reset();
    gst_deinit();
}

void CameraController::onSetup(Slave const &slave)
{
    auto const host = RtspServer::host(_config, slave.id());
    auto const port = slave.param(QStringLiteral("port"));
    auto const mountPath = RtspServer::toMountPath(slave.id());
    auto const type = slave.param(QStringLiteral("type")).value<VideoSourceType>();
    auto const params = slave.param(QStringLiteral("params")).toHash();

    _rtspServer = std::make_unique<RtspServer>(QVariantHash{
        { QStringLiteral("host"), host },
        { QStringLiteral("port"), port },
        { QStringLiteral("mount_path"), mountPath },
        { QStringLiteral("launch"), RtspServer::launch(type, params) },
    });
}
