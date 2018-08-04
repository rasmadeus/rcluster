#ifndef MAIN_VIEW_CONTROLLER_H
#define MAIN_VIEW_CONTROLLER_H

#include <QPlainTextEdit>
#include <QMainWindow>
#include "slave_controller.h"

class QSettings;

class PLUGIN_SHARED_EXPORT MainViewController : public QMainWindow, public SlaveController
{
    Q_OBJECT

public:
    explicit MainViewController(Config const &config, Plugin const &plugin, CoreClientSocket &socket);

public:
    void init() override;

protected:
    virtual void storeSettings(QSettings &settings) { Q_UNUSED(settings); }
    virtual void restoreSettings(QSettings const &settings) { Q_UNUSED(settings); }

private:
    void storeSettings();
    void restoreSettings();
};

#endif // MAIN_VIEW_CONTROLLER_H
