#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include "terminator.h"

Terminator::Terminator(QObject *parent)
    : ActiveDevice{ parent }
{
}

void Terminator::run([[maybe_unused]] QVariantHash const &params)
{
    while (!doStop())
    {
        std::string line;
        std::getline(std::cin, line);

        if (line.empty())
            continue;

        qDebug() << QStringLiteral("Terminator command:") << QString::fromStdString(line);

        if (line == "terminate")
        {
            qApp->quit();
            break;
        }
    }
}