#include <QMenuBar>
#include "experiment_center_controller.h"
#include <rtsp_server.h>
#include <config.h>
#include <globals.h>
#include <QDebug>
#include <QSettings>

ExperimentCenterController::ExperimentCenterController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithActivity{ config, plugin, corebus }
    , _dataView{ config, *this }
    , _deviceView{ config, _plugins, *this }
    , _viewActions{ _dataView, *this }
{
    gst_init(nullptr, nullptr);
    _gloop = std::make_unique<Gloop>();

    _plugins.load();

    _splitter.setContentsMargins(rcluster::layoutGap(), rcluster::layoutGap(), rcluster::layoutGap(), rcluster::layoutGap());
    _splitter.addWidget(&_deviceView);
    _splitter.addWidget(&_dataView);
    setCentralWidget(&_splitter);
    setWindowTitle(tr("Experiment center"));

    auto mainMenu = menuBar()->addMenu(tr("View"));
    _viewActions.install(*mainMenu);

    auto mainToolBar = addToolBar(tr("View"));
    _viewActions.install(*mainToolBar);

    connect(&_deviceView, &DeviceView::doubleClicked, &_dataView, &DataView::appendDeviceView);
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
    settings.setValue(QStringLiteral("splitter_geometry"), _splitter.saveGeometry());
    settings.setValue(QStringLiteral("splitter_state"), _splitter.saveState());
}

void ExperimentCenterController::restoreSettings(QSettings const &settings)
{
    _splitter.restoreGeometry(settings.value(QStringLiteral("splitter_geometry")).toByteArray());
    _splitter.restoreState(settings.value(QStringLiteral("splitter_state")).toByteArray());
}
