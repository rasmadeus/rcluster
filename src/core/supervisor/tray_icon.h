#ifndef TRAY_ICON_H
#define TRAY_ICON_H

#include <QMenu>
#include <QSystemTrayIcon>
#include <core_connect_widget.h>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit TrayIcon(CoreClientSocket &socket, QObject *parent = nullptr);

private:
    QMenu _menu;
    CoreConnectWidget _coreConnectWidget;
};

#endif // TRAY_ICON_H
