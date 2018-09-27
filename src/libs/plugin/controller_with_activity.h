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

public:
    void restoreSettings() override;

protected:
    virtual void storeSettings(QSettings &settings) const { Q_UNUSED(settings); }
    virtual void restoreSettings(QSettings &settings) { Q_UNUSED(settings); }

private:
    void storeControllerSettings() const;
};

#endif // CONTROLLER_WITH_ACTIVITY_H
