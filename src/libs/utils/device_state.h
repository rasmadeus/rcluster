#ifndef DEVICE_STATE_H
#define DEVICE_STATE_H

#include <QMetaType>

enum class DeviceState
{
    On,
    Off,
};

Q_DECLARE_METATYPE(DeviceState)

#endif // DEVICE_STATE_H