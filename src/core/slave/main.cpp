#include <QApplication>
#include <config.h>
#include <config_watcher.h>
#include <core_bus.h>
#include <log.h>
#include <message.h>
#include <plugins.h>
#include <slave_controller.h>
#include <crash_handler.h>
#include <translator.h>
#include "args.h"

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };

    auto const args = Args::make(QCoreApplication::arguments());
    rcluster::initLogging(args.type.toLower(), args.id);
    CrashHandler::handle(args.type.toLower(), args.id);

    Translator{ args.type };

    auto plugin = Plugins::load(args.type);
    Q_ASSERT(plugin);

    qRegisterMetaType<Message>("Message");

    Config config;
    ConfigWatcher configWatcher{ config };
    Corebus corebus{ args.id };

    auto controller = plugin->controller();
    Q_ASSERT(controller != nullptr);

    controller->setConfig(config);
    controller->setPlugin(*plugin);
    controller->setCorebus(corebus);
    controller->init();

    QObject::connect(&corebus, &Corebus::ready, [&controller, &configWatcher](auto const &message){
        if (!configWatcher.route(message))
            controller->onMessage(message);
    });

    corebus.connectToHost(args.host, args.port);

    return app.exec();
}
