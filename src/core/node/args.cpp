#include <QCoreApplication>
#include "args.h"

Args Args::make(QStringList const &args)
{
    Q_ASSERT(args.size() == 5);
    return { args };
}

Args::Args(QStringList const &args)
    : type{ args[1] }
    , id{ QUuid::fromString(args[2]) }
    , host{ args[3] }
    , port{ static_cast<quint16>(args[4].toInt()) }
{
}
