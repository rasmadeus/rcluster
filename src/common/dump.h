#ifndef DUMP_H
#define DUMP_H

#include <fstream>
#include <signal.h>
#include <boost/filesystem.hpp>
#include <boost/stacktrace.hpp>
#include <QtGlobal>
#include <QDebug>
#include "globals.h"

namespace rcluster
{
    inline void logDump()
    {
        auto const pathToDump = rcluster::dumpPath().toStdString();
        if (boost::filesystem::exists(pathToDump))
        {
            std::ifstream ifs{ pathToDump };
            auto const st = boost::stacktrace::stacktrace::from_dump(ifs);
            for(auto const &line : st.as_vector())
                qDebug() << QString::fromStdString(line.source_file()) << ":" << line.source_line() << QString::fromStdString(line.name());
            ifs.close();
        }
    }

    inline void signalHandler(int signum)
    {
        ::signal(signum, SIG_DFL);
        qDebug() << "Signal" << signum << ". Created dump file with size" << boost::stacktrace::safe_dump_to(rcluster::dumpPath().toStdString().c_str());
        ::raise(SIGABRT);
    }

    inline void catchCrash()
    {
        auto const dumpsDir = rcluster::dumpsLocation().toStdString();
        if (!boost::filesystem::exists(dumpsDir))
            if (!boost::filesystem::create_directories(dumpsDir))
                qWarning() << "Failed to create" << rcluster::dumpsLocation();

        logDump();

        ::signal(SIGSEGV, &signalHandler);
        ::signal(SIGABRT, &signalHandler);
    }
}

#endif //DUMP_H
