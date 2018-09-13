#include "experiment_center_controller.h"
#include <rtsp_server.h>
#include <config.h>
#include <QDebug>

ExperimentCenterController::ExperimentCenterController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithActivity{ config, plugin, corebus }
{
    gst_init(nullptr, nullptr);
    _gloop = std::make_unique<Gloop>();

    setWindowTitle(tr("Experiment center"));
}

ExperimentCenterController::~ExperimentCenterController()
{
    _gloop.reset();
    gst_deinit();
}

void ExperimentCenterController::onSetup(Slave const &slave)
{
}
