#ifndef ARGS_H
#define ARGS_H

#include <QDebug>
#include <QString>
#include <QUuid>

struct Args
{
    static Args make(QStringList const &args);
    Args(QStringList const &args);

    void log() const { qDebug() << "Args:" << type << id << host << port; }

    QString const type;
    QUuid const id;
    QString const host;
    quint16 const port;
};

#endif // ARGS_H
