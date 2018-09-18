#ifndef DEVICE_DATA_VIEW_H
#define DEVICE_DATA_VIEW_H

#include <QMdiArea>

class Config;

class DeviceDataView : public QMdiArea
{
    Q_OBJECT

public:
    explicit DeviceDataView(Config const &config, QWidget &parent);

public:
    void appendView(QUuid const &id, QString const &type);

private:
    QWidget *make(QUuid const &id, QString const &type, QWidget &parent) const;

private:
    Config const &_config;
};

#endif // DEVICE_DATA_VIEW_H
