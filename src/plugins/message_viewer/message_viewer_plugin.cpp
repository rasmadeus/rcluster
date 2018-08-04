#include "main_view.h"
#include "message_viewer_plugin.h"
#include "message_viewer_editor.h"

Editor *MessageViewerPlugin::editor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent) const
{
    return new MessageViewerEditor{ config, plugins, socket, id, parent };
}

std::unique_ptr<SlaveController> MessageViewerPlugin::controller(Config const &config, Plugin const &plugin, CoreClientSocket &socket) const
{
    return std::unique_ptr<SlaveController>(new MainView{ config, plugin, socket });
}
