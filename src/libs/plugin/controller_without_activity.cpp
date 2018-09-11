#include "controller_without_activity.h"

ControllerWithoutActivity::ControllerWithoutActivity(Config const &config, Plugin const &plugin, Corebus &corebus)
    : QWidget{}
    , SlaveController{ config, plugin, corebus }
{
    catchWmExitGeneratedBySupervistor();
}

void ControllerWithoutActivity::catchWmExitGeneratedBySupervistor()
{
    setGeometry(0, 0, 0, 0);
    show();
}
