#ifndef TRAY_ICON_H
#define TRAY_ICON_H

#include <QMenu>
#include <QSystemTrayIcon>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit TrayIcon(QObject * parent = nullptr);

private:
    QMenu _menu;
};

#endif // TRAY_ICON_H
