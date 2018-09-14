#include "experiment_center_controller.h"
#include <rtsp_server.h>
#include <config.h>
#include <globals.h>
#include <QDebug>
#include <QSettings>

ExperimentCenterController::ExperimentCenterController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithActivity{ config, plugin, corebus }
    , _deviceView{ config, _plugins }
{
    gst_init(nullptr, nullptr);
    _gloop = std::make_unique<Gloop>();

    _plugins.load();

    _splitter.setContentsMargins(rcluster::layoutGap(), rcluster::layoutGap(), rcluster::layoutGap(), rcluster::layoutGap());
    _splitter.addWidget(&_deviceView);
    _splitter.addWidget(&_dataView);
    setCentralWidget(&_splitter);
    setWindowTitle(tr("Experiment center"));
}

ExperimentCenterController::~ExperimentCenterController()
{
    _gloop.reset();
    gst_deinit();
}

void ExperimentCenterController::onSetup(Slave const &slave)
{
    _deviceView.onSetup(slave);
}

void ExperimentCenterController::storeSettings(QSettings &settings)
{
    settings.setValue(QStringLiteral("splitter_state"), _splitter.saveState());
    settings.setValue(QStringLiteral("splitter_geometry"), _splitter.saveGeometry());
}

void ExperimentCenterController::restoreSettings(QSettings const &settings)
{
    _splitter.restoreState(settings.value(QStringLiteral("splitter_state")).toByteArray());
    _splitter.restoreGeometry(settings.value(QStringLiteral("splitter_geometry")).toByteArray());
}
