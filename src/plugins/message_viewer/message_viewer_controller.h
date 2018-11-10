#ifndef MESSAGE_VIEWER_CONTROLLER_H
#define MESSAGE_VIEWER_CONTROLLER_H

#include <QPlainTextEdit>
#include <controller_with_activity.h>

class MessageViewerController : public ControllerWithActivity
{
    Q_OBJECT

public:
    explicit MessageViewerController(Config const &config, Plugin const &plugin, Corebus &corebus);

public:
    void onMessage(Message const &message) override;
    void onSetup([[maybe_unused]] Node const &node) override {}

private:
    int _count{ 0 };
    QPlainTextEdit _log;
};

#endif // MESSAGE_VIEWER_CONTROLLER_H
