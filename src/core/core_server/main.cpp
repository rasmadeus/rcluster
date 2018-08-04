#include <QApplication>
#include <QWidget>
#include <config.h>
#include <dump.h>
#include <log.h>
#include <message.h>
#include <translator.h>
#include "config_storage.h"
#include "server.h"
#include "tray_icon.h"

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };

    rcluster::initLogging(QStringLiteral("core_server"));
    rcluster::catchCrash();
    Translator{};
    qRegisterMetaType<Message>("Message");

    Config config;
    ConfigStorage configStorage{ config };
    Server server{ rcluster::corePort(), config };

    TrayIcon trayIcon;
    trayIcon.show();

    return app.exec();
}
