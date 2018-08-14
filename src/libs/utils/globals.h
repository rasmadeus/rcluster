#ifndef GLOBALS_H
#define GLOBALS_H

#include <QCoreApplication>
#include <QtGlobal>
#include <QStandardPaths>
#include "utils_global.h"

namespace rcluster
{
    inline int UTILS_SHARED_EXPORT layoutGap() { return 6; }
    inline quint16 UTILS_SHARED_EXPORT corePort() { return 13000; }
    inline QString UTILS_SHARED_EXPORT writableLocation() { return QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QStringLiteral("/rcluster"); }
    inline QString UTILS_SHARED_EXPORT dumpsLocation() { return writableLocation() + QStringLiteral("/dumps"); }
    inline QString UTILS_SHARED_EXPORT pathToFileConfig() { return QStringLiteral("%1/config_server.txt").arg(writableLocation()); }
    inline QString UTILS_SHARED_EXPORT organizationName() { return QStringLiteral("rcluster"); }
    inline QString UTILS_SHARED_EXPORT logsLocation() { return writableLocation() + QStringLiteral("/logs"); }
}

#endif //GLOBALS_H
