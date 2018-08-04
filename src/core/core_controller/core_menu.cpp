#include <QApplication>
#include <QMainWindow>
#include <core_client_socket.h>
#include "core_menu.h"

CoreMenu::CoreMenu(CoreClientSocket &coreClientSocket, QMainWindow &parent)
    : Menu(tr("Core"), parent)
    , _coreClientSocket{ coreClientSocket }
    , _socketConnectWidget{ coreClientSocket, &parent }
{
    _menu.addAction(tr("Show connect dialog"), std::bind(&CoreConnectWidget::show, &_socketConnectWidget));
    _menu.addSeparator();
    _menu.addAction(tr("Exit core and slaves"), std::bind(&CoreMenu::exitCoreAndSlaves, this));

    install(*parent.menuBar());
}

void CoreMenu::exitCoreAndSlaves()
{
    _coreClientSocket.send(QStringLiteral("EXIT"));
}
