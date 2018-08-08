#include <QMenu>
#include <QToolBar>
#include <svg.h>
#include "actions.h"

Actions::Actions(QObject &parent)
    : QObject{ &parent }
{
}

QAction &Actions::append(QString const &icon, QString const &name, bool afterSeparator)
{
    _actions.emplace_back(std::make_unique<QAction>(rcluster::fromSvg(icon, { 32, 32 }), name), afterSeparator);
    return *_actions.back().first.get();
}
