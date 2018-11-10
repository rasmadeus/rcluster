#include <QApplication>
#include "tray_icon.h"

TrayIcon::TrayIcon(QObject *parent)
    : QSystemTrayIcon{ parent }
{
    _menu.addAction(tr("Exit"), qApp, &QCoreApplication::quit);
    setContextMenu(&_menu);
    setToolTip(QStringLiteral("Core"));
    setIcon(QIcon{ QStringLiteral(":/res/icon.ico") });
}
