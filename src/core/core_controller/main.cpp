#include <QApplication>
#include <QMetaType>
#include <QTcpSocket>
#include <config.h>
#include <config_watcher.h>
#include <log.h>
#include <globals.h>
#include <corebus.h>
#include <device.h>
#include <message.h>
#include <plugins.h>
#include <crash_handler.h>
#include <translator.h>
#include "main_view.h"

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };

    Log log;
    log.init(app.applicationName());

    CrashHandler::handle(app.applicationName());

    Translator{ Translator::Type::AppAndPlugins };
    qRegisterMetaType<Message>("Message");
    qRegisterMetaType<Device::State>("Device::State");
    QApplication::setOrganizationName(rcluster::organizationName());

    Config config;
    ConfigWatcher configWatcher{ config };

    Plugins plugins;
    plugins.load();

    Corebus socket{ QUuid::createUuid() };
    QObject::connect(&socket, &Corebus::ready, [&configWatcher, &app](Message const &message){
        if (!configWatcher.route(message) && message.action() == QStringLiteral("EXIT"))
            app.quit();
    });

    ControllerWithActivity mainView{ config, plugins, socket };
    mainView.show();

    return app.exec();
}
