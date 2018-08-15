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
    Supervisors supervisors{ config, plugins };

    QObject::connect(&corebus, &Corebus::connected, [&supervisors, &corebus]{
        supervisors.setCoreAddress(corebus.host(), QString::number(corebus.port()));
    });

    QObject::connect(&supervisors, &Supervisors::processStateChanged, [&corebus](QUuid const &id, QProcess::ProcessState state){
        corebus.send(QStringLiteral("PROCESS"), QStringLiteral("core"), {
            { QStringLiteral("slave"), id },
            { QStringLiteral("process_state"), state },
        });
    });

    QObject::connect(&corebus, &Corebus::ready, [&configWatcher, &app](Message const &message){
        if (!configWatcher.route(message) && message.action() == QStringLiteral("EXIT"))
            app.quit();
    });

    TrayIcon trayIcon{ corebus };
    trayIcon.show();

    return app.exec();
}
