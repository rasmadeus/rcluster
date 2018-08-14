#ifndef DUMP_H
#define DUMP_H

#include <fstream>
#include <csignal>
#include <boost/filesystem.hpp>
#include <boost/stacktrace.hpp>
#include <QtGlobal>
#include <QDebug>
#include "globals.h"

class CrashHandler
{
public:
    static void handle(QString const &type, QUuid const &id = {})
    {
        _crashHandler.setPath(type, id);
        _crashHandler.start();
    }

    CrashHandler(CrashHandler const &other) = delete;
    CrashHandler &operator = (CrashHandler const &other) = delete;

public:
    void start()
    {
        logPrevDump();
        createLogDir();
        std::signal(SIGSEGV, &CrashHandler::signalHandler);
        std::signal(SIGABRT, &CrashHandler::signalHandler);
    }

    void setPath(QString const &type, QUuid const &id)
    {
        _pathToDump = rcluster::dumpPath(type, id);
    }

    QString const &path() const
    {
        return _pathToDump;
    }

private:
    CrashHandler() = default;

    static void signalHandler(int signum)
    {
        std::signal(signum, SIG_DFL);
        boost::stacktrace::safe_dump_to(_crashHandler.path().toStdString().c_str());
        std::raise(SIGABRT);
    }

private:
    void createLogDir()
    {
        auto const dumpsDir = rcluster::dumpsLocation().toStdString();
        if (!boost::filesystem::exists(dumpsDir))
            if (!boost::filesystem::create_directories(dumpsDir))
                qWarning() << "Failed to create" << rcluster::dumpsLocation();
    }

    void logPrevDump()
    {
        if (boost::filesystem::exists(_pathToDump.toStdString()))
        {
            qDebug() << "Found crash dump at" << _pathToDump;
            std::ifstream ifs{ _pathToDump.toStdString() };
            auto const st = boost::stacktrace::stacktrace::from_dump(ifs);
            for(auto const &line : st.as_vector())
                qDebug() << QString::fromStdString(line.source_file()) << ":" << line.source_line() << QString::fromStdString(line.name());
            ifs.close();
        }
    }

private:
    static CrashHandler _crashHandler;
    QString _pathToDump;
};

CrashHandler CrashHandler::_crashHandler;

#endif //DUMP_H
