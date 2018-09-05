#include <QDebug>
#include "device.h"

Device::Device(QObject *parent)
    : QObject{ parent }
{
}

void Device::logError(QString const &what)
{
    qCritical() << what;
    emit error(what);
}
