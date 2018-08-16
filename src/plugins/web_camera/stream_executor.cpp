#include "stream_executor.h"
#include "camera.h"

StreamExecutor::StreamExecutor(const QString &name, QObject *parent)
    : QThread{ parent }
    , _name{ name }
{
}

void StreamExecutor::run()
{
    Camera cam{ _name };
    exec();
}
