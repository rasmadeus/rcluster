#ifndef EXPERIMENT_CENTER_CONTROLLER_H
#define EXPERIMENT_CENTER_CONTROLLER_H

#include <memory>
#include <gloop.h>
#include <rtsp_client.h>
#include <QPlainTextEdit>
#include <controller_with_activity.h>

class ExperimentCenterController : public ControllerWithActivity
{
    Q_OBJECT

public:
    explicit ExperimentCenterController(Config const &config, Plugin const &plugin, Corebus &corebus);
    ~ExperimentCenterController() override;

public:
    void onSetup(Slave const &slave) override;

private:
    QWidget _widget;
    std::unique_ptr<Gloop> _gloop;
    std::unique_ptr<RtspClient> _client;
};

#endif // EXPERIMENT_CENTER_CONTROLLER_H