#include "experiment_center_controller.h"
#include "experiment_center_plugin.h"
#include "experiment_center_editor.h"

Editor *ExperimentCenterPlugin::editor(EditorData const &data, QWidget &parent) const
{
    return new ExperimentCenterEditor{ data, parent };
}

std::unique_ptr<SlaveController> ExperimentCenterPlugin::controller(Config const &config, Plugin const &plugin, Corebus &corebus) const
{
    return std::make_unique<ExperimentCenterController>(config, plugin, corebus);
}
