#include <config.h>
#include <core_bus.h>
#include "controller.h"
#include "stream_executor.h"

Controller::Controller()
    : QObject{}
    , SlaveController{}
{
}

void Controller::onSetup(Slave const &slave)
{
    Q_UNUSED(slave)
    auto ex = new StreamExecutor{ slave.param("name").toString(), this };
    connect(ex, &StreamExecutor::finished, ex, &StreamExecutor::deleteLater);
    ex->start();
}
