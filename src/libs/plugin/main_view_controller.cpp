#include <QApplication>
#include <QLayout>
#include <QSettings>
#include <core_client_socket.h>
#include <globals.h>
#include <message.h>
#include "main_view_controller.h"
#include "plugin.h"

MainViewController::MainViewController(Config const &config, Plugin const &plugin, CoreClientSocket &socket)
    : QMainWindow{ nullptr, Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint }
    , SlaveController{ config, plugin, socket }
{
    setWindowIcon(plugin.pixmap({ 32, 32}));
    setContentsMargins(rcluster::layoutGap(), rcluster::layoutGap(), rcluster::layoutGap(), rcluster::layoutGap());
    connect(qApp, &QApplication::aboutToQuit, this, static_cast<void(MainViewController::*)()>(&MainViewController::storeSettings));
}

void MainViewController::init()
{
    restoreSettings();
    show();
}

void MainViewController::storeSettings()
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("main_view"));
    settings.setValue(QStringLiteral("geometry"), saveGeometry());
    settings.setValue(QStringLiteral("state"), saveState());
    storeSettings(settings);
    settings.endGroup();
}

void MainViewController::restoreSettings()
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("main_view"));
    restoreGeometry(settings.value(QStringLiteral("geometry")).toByteArray());
    restoreState(settings.value(QStringLiteral("state")).toByteArray());
    restoreSettings(settings);
    settings.endGroup();
}
