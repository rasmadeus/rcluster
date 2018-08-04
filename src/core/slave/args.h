#ifndef ARGS_H
#define ARGS_H

#include <QString>
#include <QUuid>

struct Args
{
    static Args make(QStringList const &args);
    Args(QStringList const &args);

    QString const type;
    QUuid const id;
    QString const host;
    quint16 const port;
};

#endif // ARGS_H
