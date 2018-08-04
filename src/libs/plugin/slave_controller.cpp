#include "slave_controller.h"

SlaveController::SlaveController(Config const &config, Plugin const &plugin, CoreClientSocket &socket)
    : _config{ config }
    , _plugin{ plugin }
    , _socket{ socket }
{
}
