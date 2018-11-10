#ifndef DEFAULT_DEVICE_H
#define DEFAULT_DEVICE_H

#include "device.h"

class UTILS_SHARED_EXPORT DefaultDevice : public Device
{
    Q_OBJECT

public:
    explicit DefaultDevice(QObject *parent = nullptr);

public:
    Device::State state() const override { return _state; }
    QString const &lastError() const override { return _lastError; }

private:
    void setState(State state) { _state = state; }
    void setLastError(QString const &what) { _lastError = what; }

private:
    State _state{ State::Off };
    QString _lastError;
};

#endif // DEFAULT_DEVICE_H
