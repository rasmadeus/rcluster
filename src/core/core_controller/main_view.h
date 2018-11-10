#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <QMainWindow>
#include <QSplitter>
#include "core_actions.h"
#include "config_view.h"
#include "node_params_view.h"

class Corebus;
class Plugins;

class ControllerWithActivity : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControllerWithActivity(Config &config, Plugins &plugins, Corebus &corebus);

private:
    void storeSettings() const;
    void restoreSettings();
    void onCoreConnected();
    void onCoreDisconnected();

private:
    Corebus &_corebus;
    CoreActions _coreActions;
    QSplitter _splitter;
    ConfigView _configView;
    NodeParamsView _nodeParamsView;
};

#endif // MAIN_VIEW_H
