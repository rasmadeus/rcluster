#include <QMenu>
#include <QToolBar>
#include "actions.h"

QAction &Actions::append(QString const &icon, QString const &name, bool afterSeparator)
{
    _actions.emplace_back(std::make_unique<QAction>(QIcon{ icon }, name), afterSeparator);
    return *_actions.back().first.get();
}
