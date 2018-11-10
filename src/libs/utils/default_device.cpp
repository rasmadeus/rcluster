#include <QDebug>
#include "device.h"
#include "default_device.h"

DefaultDevice::DefaultDevice(QObject *parent)
    : Device{ parent }
{
    connect(this, &DefaultDevice::error, this, &DefaultDevice::setLastError);
    connect(this, &DefaultDevice::stateChanged, this, &DefaultDevice::setState);
}
