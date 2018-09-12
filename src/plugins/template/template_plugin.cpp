#include "template_controller.h"
#include "template_plugin.h"
#include "template_editor.h"

Editor *TeamplatePlugin::editor(EditorData const &data, QWidget &parent) const
{
    return new TemplateEditor{ data, parent };
}

std::unique_ptr<SlaveController> TeamplatePlugin::controller(Config const &config, Plugin const &plugin, Corebus &corebus) const
{
    return std::make_unique<TemplateController>(config, plugin, corebus);
}
