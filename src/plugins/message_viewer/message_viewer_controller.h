#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <QPlainTextEdit>
#include <controller_with_activity.h>

class MessageViewerController : public ControllerWithActivity
{
    Q_OBJECT

public:
    explicit MessageViewerController();

public:
    void onMessage(Message const &message) override;
    void onSetup(Slave const &slave) override { Q_UNUSED(slave) }

private:
    int _count{ 0 };
    QPlainTextEdit _log;
};

#endif // MAIN_VIEW_H
