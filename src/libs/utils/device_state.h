#ifndef DEVICE_STATE_H
#define DEVICE_STATE_H

#include <QMetaType>

enum class DeviceState
{
    Unknown,
    On,
    Off,
};

namespace std
{
    template <> struct hash<DeviceState>
    {
        size_t operator() (DeviceState state) const { return static_cast<std::size_t>(state); }
    };
}

Q_DECLARE_METATYPE(DeviceState)

#endif // DEVICE_STATE_H
