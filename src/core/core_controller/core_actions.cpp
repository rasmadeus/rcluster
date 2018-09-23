#include <QMainWindow>
#include <corebus.h>
#include "core_actions.h"

CoreActions::CoreActions(Corebus &corebus, QMainWindow &parent)
    : Actions{ parent }
    , _corebus{ corebus }
    , _coreConnectWidget{ corebus, &parent }
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
    _corebus.send(QStringLiteral("EXIT"));
}
