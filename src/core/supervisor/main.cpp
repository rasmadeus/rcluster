#include <QApplication>
#include <QMetaType>
#include <config.h>
#include <config_watcher.h>
#include <dump.h>
#include <log.h>
#include <core_bus.h>
#include <message.h>
#include <plugins.h>
#include <translator.h>
#include "supervisors.h"
#include "tray_icon.h"

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };

    rcluster::initLogging(QStringLiteral("supervisor"));
    CrashHandler::handle(QStringLiteral("supervisor"));
    Translator{ Translator::Type::AppAndPlugins };
    qRegisterMetaType<Message>("Message");

    QApplication::setOrganizationName(rcluster::organizationName());
    QApplication::setQuitOnLastWindowClosed(false);

    Config config;
    ConfigWatcher configWatcher{ config };

    Plugins plugins;
    plugins.load();

    Corebus socket{ QUuid::createUuid() };
    Supervisors processes{ config, plugins };

    QObject::connect(&socket, &Corebus::connected, [&processes, &socket]{
        processes.setCoreAddress(socket.host(), QString::number(socket.port()));
    });

    QObject::connect(&socket, &Corebus::ready, [&configWatcher, &app](Message const &message){
        if (!configWatcher.route(message) && message.action() == QStringLiteral("EXIT"))
            app.quit();
    });

    TrayIcon trayIcon{ socket };
    trayIcon.show();

    return app.exec();
}
