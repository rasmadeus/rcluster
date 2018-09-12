#include <QApplication>
#include <QWidget>
#include <config.h>
#include <log.h>
#include <message.h>
#include <plugins.h>
#include <crash_handler.h>
#include <translator.h>
#include "params_cleaner.h"
#include "config_storage.h"
#include "server.h"
#include "tray_icon.h"

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };

    Log log;
    log.init(app.applicationName());

    CrashHandler::handle(app.applicationName());
    Translator{};
    qRegisterMetaType<Message>("Message");

    Plugins plugins;
    plugins.load();

    Config config;
    ParamsCleaner paramsCleaner{ config, plugins };
    ConfigStorage configStorage{ config, plugins };
    Server server{ rcluster::corePort(), config, plugins };

    TrayIcon trayIcon;
    trayIcon.show();

    return app.exec();
}
