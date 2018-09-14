#ifndef DEVICE_VIEW_H
#define DEVICE_VIEW_H

#include <QTreeView>
#include <slave_sort_model.h>
#include "device_model.h"

class Config;
class Plugins;
class Slave;

class DeviceView : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceView(Config const &config, Plugins const &plugins, QWidget *parent = nullptr);

public:
    void onSetup(Slave const &slave);

private:
    Config const &_config;
    QTreeView _view;
    DeviceModel _model;
    SlaveSortModel _proxyModel;
};

#endif // DEVICE_VIEW_H
