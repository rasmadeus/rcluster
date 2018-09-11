#include "experiment_center_controller.h"
#include <rtsp_server.h>
#include <config.h>
#include <QDebug>

ExperimentCenterController::ExperimentCenterController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithActivity{ config, plugin, corebus }
{
    _widget.setAttribute(Qt::WA_NativeWindow);
    setCentralWidget(&_widget);

    gst_init(nullptr, nullptr);

    _gloop = std::make_unique<Gloop>();

    setWindowTitle(tr("Experiment center"));
}

ExperimentCenterController::~ExperimentCenterController()
{
    _client.reset();
    gst_deinit();
}

void ExperimentCenterController::onSetup(Slave const &slave)
{
    auto cames = _config.slaves(QStringLiteral("CAMERA"));
    auto url = RtspServer::url(_config, cames.toList().first());
    qDebug() << "Url:" << url;
    _client = std::make_unique<RtspClient>(url, _widget.winId());
}
