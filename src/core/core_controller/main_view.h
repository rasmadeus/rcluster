#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <QMainWindow>
#include <QSplitter>
#include <core_menu.h>
#include "config_view.h"
#include "slave_params_view.h"

class CoreClientSocket;
class Plugins;

class MainViewController : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainViewController(Config &config, Plugins &plugins, CoreClientSocket &socket);

private:
    void storeSettings();
    void restoreSettings();
    void onCoreConnected();
    void onCoreDisconnected();

private:
    CoreClientSocket &_socket;
    CoreMenu _coreMenu;
    QSplitter _splitter;
    ConfigView _configView;
    SlaveParamsView _slaveParamsView;
};

#endif // MAIN_VIEW_H
