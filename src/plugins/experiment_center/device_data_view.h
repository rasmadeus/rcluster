#ifndef DEVICE_DATA_VIEW_H
#define DEVICE_DATA_VIEW_H

#include <QMdiSubWindow>
#include <QUuid>

class Config;

class DeviceDataView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit DeviceDataView(QUuid const &id, Config const &config, QWidget &parent);

public:
    QUuid const &id() const { return _id; }

private:
    void updateTitle();
    void onSlaveRenamed(QUuid const &id);

private:
    QUuid const _id;
    Config const &_config;
};

#endif // DEVICE_DATA_VIEW_H
