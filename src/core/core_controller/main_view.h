#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <QMainWindow>
#include <QSplitter>
#include "core_actions.h"
#include "config_view.h"
#include "slave_params_view.h"

class Corebus;
class Plugins;

class MainViewController : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainViewController(Config &config, Plugins &plugins, Corebus &corebus);

private:
    void storeSettings();
    void restoreSettings();
    void onCoreConnected();
    void onCoreDisconnected();

private:
    Corebus &_corebus;
    CoreActions _coreActions;
    QSplitter _splitter;
    ConfigView _configView;
    SlaveParamsView _slaveParamsView;
};

#endif // MAIN_VIEW_H
