#include <QCoreApplication>
#include <slave_facade.h>
#include "controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication app{ argc, argv };
    SlaveFacade slaveFacade{ [](Config const &config, CoreClientSocket &socket){
        return std::make_unique<Controller>(config, socket);
    } };
    return app.exec();
}
