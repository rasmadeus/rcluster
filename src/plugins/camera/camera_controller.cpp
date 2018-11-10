extern "C"
{
    #include <gst/gst.h>
}

#include <config.h>
#include <corebus.h>
#include <video_source_type.h>
#include <rtsp_server.h>
#include "camera_controller.h"

CameraController::CameraController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : DeviceController{ config, plugin, corebus, std::make_unique<RtspServer>() }
{
    gst_init(nullptr, nullptr);
    _gloop = std::make_unique<Gloop>();
}

CameraController::~CameraController()
{
    _device->stop();
    _gloop.reset();
    gst_deinit();
}

void CameraController::start(Node const &node)
{
    auto const host = RtspServer::host(_config, node.id());
    auto const port = node.param(QStringLiteral("port"));
    auto const mountPath = RtspServer::toMountPath(node.id());
    auto const type = node.param(QStringLiteral("type")).value<VideoSourceType>();
    auto const params = node.param(QStringLiteral("params")).toHash();

    _device->start(QVariantHash{
        { QStringLiteral("host"), host },
        { QStringLiteral("port"), port },
        { QStringLiteral("mount_path"), mountPath },
        { QStringLiteral("launch"), RtspServer::launch(type, params) },
    });
}
