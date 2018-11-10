#include "node_controller.h"

NodeController::NodeController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : _config{ config }
    , _plugin{ plugin }
    , _corebus{ corebus }
{
}
