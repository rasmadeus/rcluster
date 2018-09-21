#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <memory>
#include <controller_without_activity.h>
#include <gloop.h>
#include <rtsp_server.h>
#include <gst_pipeline_observer.h>

class CameraController : public ControllerWithoutActivity
{
    Q_OBJECT

public:
    explicit CameraController(Config const &config, Plugin const &plugin, Corebus &corebus);
    ~CameraController() override;

public:
    void onSetup(Slave const &slave) override;

private:
    void onRtspServerStateChanged(DeviceState state);

private:
    RtspServer _rtspServer;
    std::unique_ptr<Gloop> _gloop;
};

#endif // CAMERA_CONTROLLER_H
