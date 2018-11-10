#ifndef CONTROLLER_WITH_ACTIVITY_H
#define CONTROLLER_WITH_ACTIVITY_H

#include <QMainWindow>
#include "node_controller.h"

class QSettings;

class PLUGIN_SHARED_EXPORT ControllerWithActivity : public QMainWindow, public NodeController
{
    Q_OBJECT

public:
    explicit ControllerWithActivity(Config const &config, Plugin const &plugin, Corebus &corebus);

public:
    void restoreSettings() override;

protected:
    virtual void storeSettings([[maybe_unused]] QSettings &settings) const {}
    virtual void restoreSettings([[maybe_unused]] QSettings &settings) {}

private:
    void storeControllerSettings() const;
};

#endif // CONTROLLER_WITH_ACTIVITY_H
