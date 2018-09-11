#include "message_viewer_controller.h"
#include "message_viewer_plugin.h"
#include "message_viewer_editor.h"

Editor *MessageViewerPlugin::editor(EditorData const &data, QWidget &parent) const
{
    return new MessageViewerEditor{ data, parent };
}

std::unique_ptr<SlaveController> MessageViewerPlugin::controller(Config const &config, Plugin const &plugin, Corebus &corebus) const
{
    return std::make_unique<MessageViewerController>(config, plugin, corebus);
}
