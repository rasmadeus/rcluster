#include <QMainWindow>
#include <core_client_socket.h>
#include "core_actions.h"

CoreActions::CoreActions(CoreClientSocket &socket, QMainWindow &parent)
    : Actions{ parent }
    , _socket{ socket }
    , _coreConnectWidget{ socket, &parent }
{
    connect(
        &append(QStringLiteral("connect_dialog"), tr("Show connect dialog"), true),
        &QAction::triggered,
        &_coreConnectWidget,
        &CoreConnectWidget::show
    );

    connect(
        &append(QStringLiteral("exit_core"), tr("Exit core and slaves"), true),
        &QAction::triggered,
        this,
        &CoreActions::exitCoreAndSlaves
    );
}

void CoreActions::exitCoreAndSlaves()
{
    _socket.send(QStringLiteral("EXIT"));
}
