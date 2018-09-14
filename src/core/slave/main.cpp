#include <QApplication>
#include <QLabel>
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

    QApplication::setOrganizationName(rcluster::organizationName());
    QApplication::setApplicationName(plugin->type().toLower());

    qRegisterMetaType<Message>("Message");

    Config config;
    ConfigWatcher configWatcher{ config };
    Corebus corebus{ args.id };

    auto controller = plugin->controller(config, *plugin, corebus);
    Q_ASSERT(controller != nullptr);

    QObject::connect(&config, &Config::reseted, [&controller, &corebus, &config](){
        controller->onSetup(config.slave(corebus.id()));
    });

    QObject::connect(&config, &Config::updated, [&controller, &corebus, &config, &plugin](auto const &id){
        if (id == corebus.id())
            controller->onSetup(config.slave(id));
        else if (plugin->isSlaveWatched(config, id, corebus.id()))
            controller->onSetup(config.slave(corebus.id()));
    });

    QObject::connect(&corebus, &Corebus::ready, [&controller, &configWatcher](auto const &message){
        if (!configWatcher.route(message))
            controller->onMessage(message);
    });

    corebus.connectToHost(args.host, args.port);

    return app.exec();
}
