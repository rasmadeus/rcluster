#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H

#include <memory>
#include <device.h>
#include "controller_without_activity.h"

class QSettings;

class PLUGIN_SHARED_EXPORT DeviceController : public ControllerWithoutActivity
{
    Q_OBJECT

public:
    explicit DeviceController(Config const &config, Plugin const &plugin, Corebus &corebus, std::unique_ptr<Device> &&device);

public:
    void onSetup(Node const &node) override;

protected:
    virtual void start(Node const &node);

private:
    void onStart(Message const &message);
    void onStop(Message const &message);

    void onStateChanged(Device::State state);
    void onError(QString const &what);

protected:
    std::unique_ptr<Device> _device;
};

#endif // DEVICE_CONTROLLER_H
