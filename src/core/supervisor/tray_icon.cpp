#include <QApplication>
#include "tray_icon.h"

TrayIcon::TrayIcon(CoreClientSocket &socket, QObject *parent)
    : QSystemTrayIcon{ parent }
    , _coreConnectWidget{ socket }
{
    _menu.addAction(tr("Show connect dialog"), &_coreConnectWidget, &CoreConnectWidget::show);
    _menu.addAction(tr("Exit"), qApp, &QApplication::exit);

    setContextMenu(&_menu);
    setToolTip(QStringLiteral("RCluster Supervisor"));
    setIcon(QIcon{ QStringLiteral(":/res/icon.ico") });
}
