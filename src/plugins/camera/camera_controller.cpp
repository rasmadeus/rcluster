extern "C"
{
    #include <gst/gst.h>
}

#include <config.h>
#include <corebus.h>
#include <video_source_type.h>
#include <device_state.h>
#include "camera_controller.h"

CameraController::CameraController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithoutActivity{ config, plugin, corebus }
{
    connect(&_rtspServer, &RtspServer::stateChanged, this, &CameraController::onRtspServerStateChanged);
    gst_init(nullptr, nullptr);
    _gloop = std::make_unique<Gloop>();
}

CameraController::~CameraController()
{
    _rtspServer.stop();
    _gloop.reset();
    gst_deinit();
}

void CameraController::onSetup(Slave const &slave)
{
    _rtspServer.stop();

    auto const host = RtspServer::host(_config, slave.id());
    auto const port = slave.param(QStringLiteral("port"));
    auto const mountPath = RtspServer::toMountPath(slave.id());
    auto const type = slave.param(QStringLiteral("type")).value<VideoSourceType>();
    auto const params = slave.param(QStringLiteral("params")).toHash();

    _rtspServer.start(QVariantHash{
        { QStringLiteral("host"), host },
        { QStringLiteral("port"), port },
        { QStringLiteral("mount_path"), mountPath },
        { QStringLiteral("launch"), RtspServer::launch(type, params) },
    });

    _corebus.send(QStringLiteral("RUNTIME"), QStringLiteral("core"), {
        { QStringLiteral("slave"), _corebus.id() },
        { QStringLiteral("key"), QStringLiteral("battery") },
        { QStringLiteral("value"), QStringLiteral("has cable") },
    });
}

void CameraController::onRtspServerStateChanged(DeviceState state)
{
    _corebus.send(QStringLiteral("RUNTIME"), QStringLiteral("core"), {
        { QStringLiteral("slave"), _corebus.id() },
        { QStringLiteral("key"), QStringLiteral("state") },
        { QStringLiteral("value"), static_cast<int>(state) },
    });
}
