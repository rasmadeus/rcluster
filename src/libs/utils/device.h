#ifndef DEVICE_H
#define DEVICE_H

#include <QMetaType>
#include <QObject>
#include <QVariantHash>
#include "utils_global.h"

class UTILS_SHARED_EXPORT Device : public QObject
{
    Q_OBJECT

public:
    enum class State
    {
        On,
        Calibrating,
        Off,
    };

public:
    explicit Device(QObject *parent = nullptr);

public:
    virtual void start(QVariantHash const &params) = 0;
    virtual void stop() = 0;

    virtual Device::State state() const = 0;
    virtual QString const &lastError() const = 0;

signals:
    void stateChanged(Device::State state);
    void error(QString const &what);
};

namespace std
{
    template <> struct hash<Device::State>
    {
        size_t operator() (Device::State state) const { return static_cast<std::size_t>(state); }
    };
}

inline uint qHash(Device::State state, uint seed = 0)
{
    return qHash(static_cast<int>(state), seed);
}

Q_DECLARE_METATYPE(Device::State)

#endif // DEVICE_H
