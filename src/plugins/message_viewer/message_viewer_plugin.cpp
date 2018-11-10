#include <config.h>
#include "message_viewer_controller.h"
#include "message_viewer_plugin.h"
#include "message_viewer_editor.h"

Editor *MessageViewerPlugin::editor(EditorData const &data, QWidget &parent) const
{
    return new MessageViewerEditor{ data, parent };
}

std::unique_ptr<NodeController> MessageViewerPlugin::controller(Config const &config, Plugin const &plugin, Corebus &corebus) const
{
    return std::make_unique<MessageViewerController>(config, plugin, corebus);
}

void MessageViewerPlugin::onNodeRemoved(Config &config, QUuid const &removedNode, QUuid const &thisTypeNode) const
{
    clearParamList(config, removedNode, thisTypeNode, QStringLiteral("nodes"));
}

bool MessageViewerPlugin::isListener(Config &config, QString const &messageSource, QUuid const &thisTypeNode) const
{
    return messageSource == QStringLiteral("core") || isListenerParamList(config, messageSource, thisTypeNode, QStringLiteral("nodes"));
}
