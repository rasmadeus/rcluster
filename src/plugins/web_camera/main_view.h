#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <QPlainTextEdit>
#include <main_view_controller.h>

class MainView : public MainViewController
{
    Q_OBJECT

public:
    explicit MainView(Config const &config, Plugin const &plugin, CoreClientSocket &socket);

public:
    void onMessage(Message const &message) override;
};

#endif // MAIN_VIEW_H
