#include "message_viewer_controller.h"
#include "message_viewer_plugin.h"
#include "message_viewer_editor.h"

Editor *MessageViewerPlugin::editor(QWidget &parent) const
{
    return new MessageViewerEditor{ parent };
}

std::unique_ptr<SlaveController> MessageViewerPlugin::controller() const
{
    return std::make_unique<MessageViewerController>();
}
