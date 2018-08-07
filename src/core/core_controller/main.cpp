#include <QApplication>
#include <QMetaType>
#include <QTcpSocket>
#include <config.h>
#include <config_watcher.h>
#include <dump.h>
#include <log.h>
#include <globals.h>
#include <core_client_socket.h>
#include <message.h>
#include <plugins.h>
#include <translator.h>
#include "main_view.h"

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };

    rcluster::initLogging(QStringLiteral("core_controller"));
    rcluster::catchCrash();

    Translator{ Translator::Type::AppAndPlugins };
    qRegisterMetaType<Message>("Message");
    QApplication::setOrganizationName(rcluster::organizationName());

    Config config;
    ConfigWatcher configWatcher{ config };

    Plugins plugins;
    plugins.load();

    CoreClientSocket socket{ QUuid::createUuid() };
    QObject::connect(&socket, &CoreClientSocket::ready, [&configWatcher, &app](Message const &message){
        if (!configWatcher.route(message) && message.action() == QStringLiteral("EXIT"))
            app.quit();
    });

    MainViewController mainView{ config, plugins, socket };
    mainView.show();

    return app.exec();
}