#include <QApplication>
#include <QMetaType>
#include <config.h>
#include <config_watcher.h>
#include <log.h>
#include <core_bus.h>
#include <message.h>
#include <plugins.h>
#include <crash_handler.h>
#include <translator.h>
#include "supervisors.h"
#include "tray_icon.h"

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };

    Log log;
    log.init(app.applicationName());

    CrashHandler::handle(app.applicationName());
    Translator{ Translator::Type::AppAndPlugins };
    qRegisterMetaType<Message>("Message");

    QApplication::setOrganizationName(rcluster::organizationName());
    QApplication::setQuitOnLastWindowClosed(false);

    Config config;
    ConfigWatcher configWatcher{ config };

    Plugins plugins;
    plugins.load();

    Corebus corebus{ QUuid::createUuid() };
    Supervisors processes{ config, plugins };

    QObject::connect(&corebus, &Corebus::connected, [&processes, &corebus]{
        processes.setCoreAddress(corebus.host(), QString::number(corebus.port()));
    });

    QObject::connect(&corebus, &Corebus::ready, [&configWatcher, &app](Message const &message){
        if (!configWatcher.route(message) && message.action() == QStringLiteral("EXIT"))
            app.quit();
    });

    TrayIcon trayIcon{ corebus };
    trayIcon.show();

    return app.exec();
}
