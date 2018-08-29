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

    Log log;
    log.init(args.type.toLower(), args.id);

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

    QObject::connect(&config, &Config::reseted, [&controller, &corebus, &config](){
        controller->onSetup(config.slave(corebus.id()));
    });

    QObject::connect(&config, &Config::updated, [&controller, &corebus, &config](auto const &id){
        if (id == corebus.id())
            controller->onSetup(config.slave(id));
    });

    QObject::connect(&corebus, &Corebus::ready, [&controller, &configWatcher](auto const &message){
        if (!configWatcher.route(message))
            controller->onMessage(message);
    });

    corebus.connectToHost(args.host, args.port);

    return app.exec();
}
