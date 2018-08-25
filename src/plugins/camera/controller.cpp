#include <config.h>
#include <core_bus.h>
#include "controller.h"

Controller::Controller()
    : QObject{}
    , SlaveController{}
{
}

void Controller::onSetup(Slave const &slave)
{
    Q_UNUSED(slave)
}
