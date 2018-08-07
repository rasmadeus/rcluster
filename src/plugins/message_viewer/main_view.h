#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <QPlainTextEdit>
#include <main_view_controller.h>

class MainView : public MainViewController
{
    Q_OBJECT

public:
    explicit MainView();

public:
    void onMessage(Message const &message) override;

private:
    int _count{ 0 };
    QPlainTextEdit _log;
};

#endif // MAIN_VIEW_H
