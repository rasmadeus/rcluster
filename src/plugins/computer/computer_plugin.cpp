#include "computer_plugin.h"
#include "computer_editor.h"
#include "controller.h"

QVariantHash ComputerPlugin::defaultParams() const
{
    return {
        { QStringLiteral("ip"), QStringLiteral("127.0.0.1") },
    };
}

Editor *ComputerPlugin::editor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent) const
{
    return new ComputerEditor{ config, plugins, socket, id, parent };
}

std::unique_ptr<SlaveController> ComputerPlugin::controller(Config const &config, Plugin const &plugin, CoreClientSocket &socket) const
{
    return std::unique_ptr<SlaveController>(new Controller{ config, plugin, socket });
}
