#include "active_device.h"

ActiveDevice::ActiveDevice(QObject *parent)
    : Device{ parent }
{
}

ActiveDevice::~ActiveDevice()
{
    stop();
}

void ActiveDevice::start(QVariantHash const &params)
{
    stop();
    Q_ASSERT(_thread == nullptr);
    _doStop = false;
    _thread = std::make_unique<std::thread>(&ActiveDevice::run, this, params);
}

void ActiveDevice::stop()
{
    if (_thread != nullptr)
    {
        _doStop = true;
        if (_thread->joinable())
            _thread->join();
        _thread.reset();
    }
}
