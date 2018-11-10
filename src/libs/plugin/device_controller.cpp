#include <corebus.h>
#include <config.h>
#include "device_controller.h"

DeviceController::DeviceController(Config const &config, Plugin const &plugin, Corebus &corebus, std::unique_ptr<Device> &&device)
    : ControllerWithoutActivity{ config, plugin, corebus }
    , _device{ std::move(device) }
{
    setObjectName(QStringLiteral("device_controller"));

    _router.handle(QStringLiteral("START"), std::bind(&DeviceController::onStart, this, std::placeholders::_1));
    _router.handle(QStringLiteral("STOP"), std::bind(&DeviceController::onStop, this, std::placeholders::_1));

    connect(_device.get(), &Device::stateChanged, this, &DeviceController::onStateChanged);
    connect(_device.get(), &Device::error, this, &DeviceController::onError);
}

void DeviceController::onStart([[maybe_unused]] Message const &message)
{
    if (_device->state() == Device::State::Off)
        start(_config.node(_corebus.id()));
}

void DeviceController::onStop([[maybe_unused]] Message const &message)
{
    if (_device->state() != Device::State::Off)
        _device->stop();
}

void DeviceController::onSetup(Node const &node)
{
    auto const wasStarted = _device->state() != Device::State::Off;

    _device->stop();

    if (wasStarted)
        start(node);
}

void DeviceController::start(Node const &node)
{
    _device->start(node.params());
}

void DeviceController::onStateChanged(Device::State state)
{
    _corebus.send(QStringLiteral("RUNTIME"), QStringLiteral("core"), {
        { QStringLiteral("node"), _corebus.id() },
        { QStringLiteral("key"), QStringLiteral("state") },
        { QStringLiteral("value"), static_cast<int>(state) },
    });
}

void DeviceController::onError(QString const &what)
{
    _corebus.send(QStringLiteral("ERROR"), QStringLiteral("core"), {
        { QStringLiteral("what"), what },
    });
}
