#ifndef DEVICE_RECORD_H
#define DEVICE_RECORD_H

#include <QCoreApplication>
#include <QUuid>
#include <QVariant>
#include <QPixmap>

class Config;
class Plugins;

class DeviceRecord
{
    Q_DECLARE_TR_FUNCTIONS(DeviceRecord)

public:
    DeviceRecord(Config const &config, Plugins const &plugins);

    QUuid const &respondent() const { return _respondent; }
    void setRespondent(QUuid const &respondent) { _respondent = respondent; }
    QUuid const &device() const { return _device; }
    void setDevice(QUuid const &device) { _device = device; }

    QString respondentCaption() const;
    QString deviceCaption() const;
    QPixmap respondentPixmap() const;
    QPixmap devicePixmap() const;
    QString deviceState() const;
    QPixmap deviceStatePixmap() const;
    QString batteryStatus() const;

private:
    Config const &_config;
    Plugins const &_plugins;

    QUuid _respondent;
    QUuid _device;
};

#endif // DEVICE_RECORD_H
