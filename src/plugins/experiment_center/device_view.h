#ifndef DEVICE_VIEW_H
#define DEVICE_VIEW_H

#include <QTreeView>
#include <slave_sort_model.h>
#include "device_model.h"

class QSettings;
class Config;
class Plugins;
class Slave;

class DeviceView : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceView(Config const &config, Plugins const &plugins, QWidget &parent);

public:
    void onSetup(Slave const &slave);
    void storeSettings(QSettings &settings) const;
    void restoreSettings(QSettings &settings);

signals:
    void doubleClicked(QUuid const &id, QString const &type);

private:
    void onDoubleClicked(QModelIndex const &index);

private:
    Config const &_config;
    QTreeView _view;
    DeviceModel _model;
    SlaveSortModel _proxyModel;
};

#endif // DEVICE_VIEW_H
