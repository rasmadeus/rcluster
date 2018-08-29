extern "C"
{
    #include <gst/gst.h>
}

#include <config.h>
#include <core_bus.h>
#include "camera_controller.h"

CameraController::CameraController()
    : QObject{}
    , SlaveController{}
{
    gst_init(nullptr, nullptr);
}

void CameraController::onSetup(Slave const &slave)
{
    stop();
    _runner = std::make_unique<RtspServerRunner>("127.0.0.1", "/test", "( videotestsrc is-live=1 ! x264enc ! rtph264pay name=pay0 pt=96 )");
    _runner->start();
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
