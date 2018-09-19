#ifndef DEVICE_DATA_VIEW_H
#define DEVICE_DATA_VIEW_H

#include <QMdiArea>

class Config;
class Plugins;

class DeviceDataView : public QMdiArea
{
    Q_OBJECT

public:
    explicit DeviceDataView(Config const &config, Plugins const &plugins, QWidget &parent);

public:
    void appendView(QUuid const &id, QString const &type);

private:
    QWidget *make(QUuid const &id, QString const &type, QWidget &parent) const;

private:
    Config const &_config;
    Plugins const &_plugins;
};

#endif // DEVICE_DATA_VIEW_H
