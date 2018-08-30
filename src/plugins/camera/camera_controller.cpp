extern "C"
{
    #include <gst/gst.h>
}

#include <config.h>
#include <core_bus.h>
#include "camera_controller.h"

CameraController::CameraController()
    : ControllerWithoutActivity{}
{
    gst_init(nullptr, nullptr);
}

CameraController::~CameraController()
{
    stop();
}

void CameraController::onSetup(Slave const &slave)
{
    stop();
    start(slave);
}

void CameraController::stop()
{
    if (_runner != nullptr)
    {
        _runner->stop();
        _runner->wait();
        _runner.reset();
    }
}

void CameraController::start(Slave const &slave)
{
    Q_ASSERT(_runner == nullptr);

    auto const computer = _config->parent(slave.id(), QStringLiteral("COMPUTER"));
    auto const ip = _config->slave(computer).param(QStringLiteral("ip")).toString();
    auto mountPath = slave.id().toString();
    mountPath.replace(QStringLiteral("{"), QString{});
    mountPath.replace(QStringLiteral("}"), QString{});

    _runner = std::make_unique<RtspServerRunner>(ip, QStringLiteral("/%1").arg(mountPath), "( videotestsrc is-live=1 ! x264enc ! rtph264pay name=pay0 pt=96 )");
    _runner->start();
}
