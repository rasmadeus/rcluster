#include "computer_plugin.h"
#include "computer_editor.h"
#include "controller.h"

QVariantHash ComputerPlugin::defaultParams() const
{
    return {
        { QStringLiteral("ip"), QStringLiteral("127.0.0.1") },
    };
}

Editor *ComputerPlugin::editor(QWidget &parent) const
{
    return new ComputerEditor{ parent };
}

std::unique_ptr<SlaveController> ComputerPlugin::controller() const
{
    return std::make_unique<Controller>();
}
