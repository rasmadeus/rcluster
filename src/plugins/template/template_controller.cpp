#include "template_controller.h"
#include <rtsp_server.h>
#include <config.h>
#include <QDebug>

TemplateController::TemplateController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithActivity{ config, plugin, corebus }
{
    setWindowTitle(tr("Template"));
}

void TemplateController::onSetup(Slave const &slave)
{
    Q_UNUSED(slave)
}
