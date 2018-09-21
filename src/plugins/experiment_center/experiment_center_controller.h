#ifndef EXPERIMENT_CENTER_CONTROLLER_H
#define EXPERIMENT_CENTER_CONTROLLER_H

#include <memory>
#include <gloop.h>
#include <rtsp_renderer.h>
#include <QPlainTextEdit>
#include <QSplitter>
#include <controller_with_activity.h>
#include <plugins.h>
#include "data_view.h"
#include "device_view.h"
#include "view_actions.h"

class ExperimentCenterController : public ControllerWithActivity
{
    Q_OBJECT

public:
    explicit ExperimentCenterController(Config const &config, Plugin const &plugin, Corebus &corebus);
    ~ExperimentCenterController() override;

public:
    void onSetup(Slave const &slave) override;

protected:
    void storeSettings(QSettings &settings) override;
    void restoreSettings(QSettings const &settings) override;

private:
    Plugins _plugins;
    std::unique_ptr<Gloop> _gloop;
    QSplitter _splitter;
    DataView _dataView;
    DeviceView _deviceView;
    ViewActions _viewActions;
};

#endif // EXPERIMENT_CENTER_CONTROLLER_H
