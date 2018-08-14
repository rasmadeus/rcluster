#ifndef CRASH_HANDLER_H
#define CRASH_HANDLER_H

#include <QDir>
#include <globals.h>
#include "utils_global.h"

class UTILS_SHARED_EXPORT CrashHandler
{
public:
    static void handle(QString const &type, QUuid const &id = {});

public:
    CrashHandler(CrashHandler const &other) = delete;
    CrashHandler &operator = (CrashHandler const &other) = delete;

public:
    void start();
    void setPath(QString const &type, QUuid const &id);
    QString path() const { return rcluster::dumpsLocation() + QDir::separator() + _type + _id.toString() + QStringLiteral(".dmp"); }

private:
    CrashHandler() = default;
    static void signalHandler(int signum);

private:
    void createLogDir();
    void logPrevDump();

private:
    static CrashHandler _crashHandler;
    QString _type;
    QUuid _id;
};

#endif // CRASH_HANDLER_H
