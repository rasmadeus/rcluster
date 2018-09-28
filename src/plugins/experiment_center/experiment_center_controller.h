#ifndef EXPERIMENT_CENTER_CONTROLLER_H
#define EXPERIMENT_CENTER_CONTROLLER_H

#include <controller_with_activity.h>
#include <plugins.h>
#include "experiment_center.h"
#include "experiment_actions.h"
#include "devices_view.h"

class ExperimentCenterController : public ControllerWithActivity
{
    Q_OBJECT

public:
    explicit ExperimentCenterController(Config const &config, Plugin const &plugin, Corebus &corebus);

public:
    void onSetup(Slave const &slave) override;

protected:
    void storeSettings(QSettings &settings) const override;
    void restoreSettings(QSettings &settings) override;

private:
    Plugins _plugins;
    ExperimentCenter _experimentCenter;
    ExperimentActions _experimentActions;
    DevicesView _devicesView;
};

#endif // EXPERIMENT_CENTER_CONTROLLER_H
