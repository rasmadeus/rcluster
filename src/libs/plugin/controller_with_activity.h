#ifndef CONTROLLER_WITH_ACTIVITY_H
#define CONTROLLER_WITH_ACTIVITY_H

#include <QMainWindow>
#include "slave_controller.h"

class QSettings;

class PLUGIN_SHARED_EXPORT ControllerWithActivity : public QMainWindow, public SlaveController
{
    Q_OBJECT

public:
    explicit ControllerWithActivity(Config const &config, Plugin const &plugin, Corebus &corebus);

protected:
    virtual void storeSettings(QSettings &settings) { Q_UNUSED(settings); }
    virtual void restoreSettings(QSettings const &settings) { Q_UNUSED(settings); }

private:
    void storeSettings();
    void restoreSettings();
};

#endif // CONTROLLER_WITH_ACTIVITY_H
