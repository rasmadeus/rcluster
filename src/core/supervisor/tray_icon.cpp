#include <QApplication>
#include "tray_icon.h"

TrayIcon::TrayIcon(Corebus &corebus, QObject *parent)
    : QSystemTrayIcon{ parent }
    , _coreConnectWidget{ corebus }
{
    _menu.addAction(tr("Show connect dialog"), &_coreConnectWidget, &CoreConnectWidget::show);
    _menu.addAction(tr("Exit"), qApp, &QApplication::exit);

    setContextMenu(&_menu);
    setToolTip(QStringLiteral("Supervisor"));
    setIcon(QIcon{ QStringLiteral(":/res/icon.ico") });
}
