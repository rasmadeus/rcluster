#ifndef DEVICE_WRITER_H
#define DEVICE_WRITER_H

#include <QUuid>
#include "default_device.h"

class UTILS_SHARED_EXPORT DeviceWriter : public DefaultDevice
{
    Q_OBJECT

public:
    explicit DeviceWriter(QObject *parent = nullptr);

public:
    virtual void write(QVariantHash const &data) = 0;
    virtual QString path() const = 0;

public:
    void setDir(QString const &dir) { _dir = dir; }
    QString const &dir() const { return _dir; }

    void setDevice(QUuid const &device) { _device = device; }
    QUuid const &device() const { return _device; }

protected:
    QString _dir;
    QUuid _device;
};

#endif // DEVICE_WRITER_H
