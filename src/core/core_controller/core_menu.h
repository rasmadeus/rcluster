#ifndef CORE_MENU_H
#define CORE_MENU_H

#include <menu.h>
#include <core_connect_widget.h>

class QMainWindow;

class CoreMenu : public Menu
{
    Q_OBJECT

public:
    explicit CoreMenu(CoreClientSocket &coreClientSocket, QMainWindow &parent);

private:
    void exitCoreAndSlaves();

private:
    CoreClientSocket &_coreClientSocket;
    CoreConnectWidget _socketConnectWidget;
};

#endif // CORE_MENU_H
