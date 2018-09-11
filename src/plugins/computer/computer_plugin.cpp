#include "computer_plugin.h"
#include "computer_editor.h"
#include "computer_controller.h"

Editor *ComputerPlugin::editor(EditorData const &data, QWidget &parent) const
{
    return new ComputerEditor{ data, parent };
}

std::unique_ptr<SlaveController> ComputerPlugin::controller(Config const &config, Plugin const &plugin, Corebus &corebus) const
{
    return std::make_unique<ComputerController>(config, plugin, corebus);
}
