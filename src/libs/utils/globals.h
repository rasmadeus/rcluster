#ifndef GLOBALS_H
#define GLOBALS_H

#include <QCoreApplication>
#include <QDir>
#include <QtGlobal>
#include <QStandardPaths>

namespace rcluster
{
    inline QString pseudonym() { return QStringLiteral("rcluster"); }
    inline int layoutGap() { return 6; }
    inline quint16 corePort() { return 13000; }
    inline QString writableLocation() { return QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QStringLiteral("/") + pseudonym(); }
    inline QString dumpsLocation() { return writableLocation() + QStringLiteral("/dumps"); }
    inline QString pathToFileConfig() { return writableLocation() + QStringLiteral("/config_server.txt"); }
    inline QString organizationName() { return QStringLiteral("rcluster"); }
    inline QString logsLocation() { return writableLocation() + QStringLiteral("/logs"); }
 }

#endif //GLOBALS_H
