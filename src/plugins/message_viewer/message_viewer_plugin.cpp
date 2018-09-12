#include <config.h>
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

bool MessageViewerPlugin::isListener(Config &config, QUuid const &messageSource, QUuid const &thisTypeSlave) const
{
    auto const slave = config.slave(thisTypeSlave);
    auto const slaves = slave.param(QStringLiteral("slaves")).toList();
    return std::any_of(slaves.cbegin(), slaves.cend(), [&messageSource](auto const &item){
        return messageSource == item.toUuid();
    });
}
