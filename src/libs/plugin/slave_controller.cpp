#include "slave_controller.h"

SlaveController::SlaveController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : _config{ config }
    , _plugin{ plugin }
    , _corebus{ corebus }
{
}
