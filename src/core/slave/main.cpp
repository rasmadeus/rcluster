#include <QApplication>
#include <config.h>
#include <config_watcher.h>
#include <core_client_socket.h>
#include <dump.h>
#include <log.h>
#include <message.h>
#include <plugins.h>
#include <slave_controller.h>
#include <translator.h>
#include "args.h"

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };

    auto const args = Args::make(QCoreApplication::arguments());
    rcluster::initLogging(args.type, args.id);
    rcluster::catchCrash();

    Translator{ args.type };

    auto plugin = Plugins::load(args.type);
    Q_ASSERT(plugin);

    qRegisterMetaType<Message>("Message");

    Config config;
    ConfigWatcher configWatcher{ config };
    CoreClientSocket socket{ args.id };

    auto controller = plugin->controller(config, *plugin, socket);
    Q_ASSERT(controller != nullptr);

    controller->init();

    QObject::connect(&socket, &CoreClientSocket::ready, [&controller, &configWatcher](auto const &message){
        if (!configWatcher.route(message))
            controller->onMessage(message);
    });

    socket.connectToHost(args.host, args.port);

    return app.exec();
}
