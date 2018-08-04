#include "main_view.h"
#include "web_camera_plugin.h"
#include "web_camera_editor.h"

Editor *WebCameraPlugin::editor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent) const
{
    return new WebCameraEditor{ config, plugins, socket, id, parent };
}

std::unique_ptr<SlaveController> WebCameraPlugin::controller(Config const &config, Plugin const &plugin, CoreClientSocket &socket) const
{
    return std::unique_ptr<SlaveController>(new MainView{ config, plugin, socket });
}
