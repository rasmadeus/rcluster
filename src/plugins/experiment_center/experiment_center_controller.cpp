#include <QMenuBar>
#include "experiment_center_controller.h"
#include <config.h>
#include <globals.h>
#include <QDebug>
#include <QSettings>

ExperimentCenterController::ExperimentCenterController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithActivity{ config, plugin, corebus }
    , _experimentCenter{ config, corebus, *this }
    , _experimentActions{ _experimentCenter, *this }
    , _devicesView{ config, _plugins }
{
    _plugins.load();

    setCentralWidget(&_devicesView);
    setWindowTitle(tr("Experiment center"));

    auto experimentMenu = menuBar()->addMenu(tr("Experiment"));
    experimentMenu->setObjectName(QStringLiteral("experiment_menu"));
    _experimentActions.install(*experimentMenu);

    auto experimentToolBar = addToolBar(tr("Experiment"));
    experimentToolBar->setObjectName(QStringLiteral("experiment_tool_bar"));
    _experimentActions.install(*experimentToolBar);
}

void ExperimentCenterController::onSetup(Slave const &slave)
{
    _experimentCenter.onSetup(slave);
    _devicesView.onSetup(slave);
}

void ExperimentCenterController::storeSettings(QSettings &settings) const
{
}

void ExperimentCenterController::restoreSettings(QSettings &settings)
{
}
