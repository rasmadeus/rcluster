#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <device_controller.h>
#include <gloop.h>

class CameraController : public DeviceController
{
    Q_OBJECT

public:
    explicit CameraController(Config const &config, Plugin const &plugin, Corebus &corebus);
    ~CameraController() override;

protected:
    void start(Node const &node) override;

private:
    std::unique_ptr<Gloop> _gloop;
};

#endif // CAMERA_CONTROLLER_H
