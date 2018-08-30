extern "C"
{
    #include <gst/gst.h>
}

#include <config.h>
#include <core_bus.h>
#include "fake_camera_controller.h"

FakeCameraController::FakeCameraController()
    : QObject{}
    , SlaveController{}
{
    gst_init(nullptr, nullptr);
}

void FakeCameraController::onSetup(Slave const &slave)
{
    Q_UNUSED(slave)
    stop();
    start(slave);
}

void FakeCameraController::stop()
{
    if (_runner != nullptr)
    {
        _runner->stop();
        _runner->wait();
        _runner.reset();
    }
}

void FakeCameraController::start(Slave const &slave)
{
    auto const pc = _config->parent(slave.id(), QStringLiteral("COMPUTER"));
    auto const ip = _config->slave(pc).param(QStringLiteral("ip")).toString();
    auto const mountPath = QStringLiteral("/%1").arg("test");
    auto const launch = QStringLiteral("( videotestsrc is-live=1 ! x264enc ! rtph264pay name=pay0 pt=96 )");
    _runner = std::make_unique<RtspServerRunner>(ip, mountPath, launch);
    _runner->start();
}
