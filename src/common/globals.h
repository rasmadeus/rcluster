#ifndef GLOBALS_H
#define GLOBALS_H

#include <QCoreApplication>
#include <QtGlobal>
#include <QUuid>
#include <QStandardPaths>

namespace rcluster
{
    inline int layoutGap() { return 6; }
    inline quint16 corePort() { return 13000; }
    inline QString writableLocation() { return QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QStringLiteral("/rcluster"); }
    inline QString dumpsLocation() { return writableLocation() + QStringLiteral("/dumps"); }
    inline QString dumpPath() { return dumpsLocation() + QStringLiteral("/") + QCoreApplication::applicationName() + QStringLiteral(".dmp"); }
    inline QString pathToFileConfig() { return QStringLiteral("%1/config_server.txt").arg(writableLocation()); }
    inline QString organizationName() { return QStringLiteral("rcluster"); }
    inline QString logsLocation() { return writableLocation() + QStringLiteral("/logs"); }
    inline QString logPath(QString const &type, QUuid const &id) { return logsLocation() + QStringLiteral("/") + type + id.toString() + QStringLiteral("_%N.log"); }
}

#endif //GLOBALS_H
