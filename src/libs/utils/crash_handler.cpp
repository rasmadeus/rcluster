#include <fstream>
#include <csignal>
#include <boost/filesystem.hpp>
#include <boost/stacktrace.hpp>
#include <QtGlobal>
#include <QDebug>
#include "crash_handler.h"

void CrashHandler::handle(QString const &type, QUuid const &id)
{
    _crashHandler.setPath(type, id);
    _crashHandler.start();
}

void CrashHandler::start()
{
    logPrevDump();
    createLogDir();
    std::signal(SIGSEGV, &CrashHandler::signalHandler);
    std::signal(SIGABRT, &CrashHandler::signalHandler);
}

void CrashHandler::setPath(QString const &type, QUuid const &id)
{
    _type = type;
    _id = id;
}

void CrashHandler::signalHandler(int signum)
{
    std::signal(signum, SIG_DFL);
    boost::stacktrace::safe_dump_to(_crashHandler.path().toStdString().c_str());
    std::raise(SIGABRT);
}

void CrashHandler::createLogDir()
{
    auto const dumpsDir = rcluster::dumpsLocation().toStdString();
    if (!boost::filesystem::exists(dumpsDir))
        if (!boost::filesystem::create_directories(dumpsDir))
             qWarning() << "Failed to create" << rcluster::dumpsLocation();
}

void CrashHandler::logPrevDump()
{
    auto const path = this->path();
    if (boost::filesystem::exists(path.toStdString()))
    {
        qDebug() << "Found crash dump at" << path;
        std::ifstream ifs{ path.toStdString() };
        auto const st = boost::stacktrace::stacktrace::from_dump(ifs);
        for(auto const &line : st.as_vector())
            qDebug() << QString::fromStdString(line.source_file()) << ":" << line.source_line() << QString::fromStdString(line.name());
        ifs.close();
    }
}

CrashHandler CrashHandler::_crashHandler;
