#include "controller_without_activity.h"

ControllerWithoutActivity::ControllerWithoutActivity(Config const &config, Plugin const &plugin, Corebus &corebus)
    : QObject{}
    , NodeController{ config, plugin, corebus }
{
}
