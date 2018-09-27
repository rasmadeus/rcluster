#include "lab_rest_api_controller.h"
#include "lab_rest_api_plugin.h"
#include "lab_rest_api_editor.h"

Editor *LabRestApiPlugin::editor(EditorData const &data, QWidget &parent) const
{
    return new LabRestApiEditor{ data, parent };
}

std::unique_ptr<SlaveController> LabRestApiPlugin::controller(Config const &config, Plugin const &plugin, Corebus &corebus) const
{
    return std::make_unique<LabRestApiController>(config, plugin, corebus);
}
