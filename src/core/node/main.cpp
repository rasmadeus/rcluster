#include <QApplication>
#include <device.h>
#include <log.h>
#include <crash_handler.h>
#include <translator.h>
#include <terminator.h>
#include "manager.h"

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };
    app.setQuitOnLastWindowClosed(false);

    qRegisterMetaType<Message>("Message");
    qRegisterMetaType<Device::State>("Device::State");

    auto const args = Args::make(QCoreApplication::arguments());

    Log log;
    log.init(args.type.toLower(), args.id);

    args.log();

    CrashHandler::handle(args.type.toLower(), args.id);
    Translator translator{ args.type };

    Terminator terminator;
    terminator.start({});

    Manager manager{ args };
    manager.start();

    return app.exec();
}
