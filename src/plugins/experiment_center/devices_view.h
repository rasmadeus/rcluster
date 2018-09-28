#ifndef DEVICES_VIEW_H
#define DEVICES_VIEW_H

#include <QTableView>
#include "devices_model.h"

class DevicesView : public QWidget
{
    Q_OBJECT

public:
    explicit DevicesView(Config const &config, Plugins const &plugins, QWidget *parent = nullptr);

public:
    void onSetup(Slave const &slave);

private:
    Config const &_config;
    QTableView _view;
    DevicesModel _model;
};

#endif // DEVICES_VIEW_H
