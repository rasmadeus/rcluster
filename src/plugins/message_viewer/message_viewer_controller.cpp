#include <QApplication>
#include <QLayout>
#include <QSettings>
#include <core_bus.h>
#include <message.h>
#include "message_viewer_controller.h"

MessageViewerController::MessageViewerController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithActivity{ config, plugin, corebus }
    , _log{ this }
{
    setContentsMargins(rcluster::layoutGap(), rcluster::layoutGap(), rcluster::layoutGap(), rcluster::layoutGap());
    setWindowTitle(tr("Message Viewer"));
    _log.setReadOnly(true);
    setCentralWidget(&_log);
}

void MessageViewerController::onMessage(Message const &message)
{
    ++_count;
    if (_count > 1000)
    {
        _log.clear();
        _count = 0;
    }

    _log.appendPlainText(message.toString());
}
