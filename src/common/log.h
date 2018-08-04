#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <unordered_map>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <QtGlobal>
#include "globals.h"

namespace rcluster
{
    inline void initBoostLog(QString const &type, QUuid const &id)
    {
        boost::log::add_file_log(
            boost::log::keywords::file_name = rcluster::logPath(type, id).toStdString(),
            boost::log::keywords::rotation_size = 10 * 1024 * 1024,
            boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
            boost::log::keywords::format = "[%TimeStamp%]: %Message%",
            boost::log::keywords::open_mode = ( std::ios::out | std::ios::app)
        );

        boost::log::add_common_attributes();
    }

    inline void messageOutput(QtMsgType type, QMessageLogContext const &context, QString const &msg)
    {
        Q_UNUSED(context)
        static boost::log::sources::severity_logger<boost::log::trivial::severity_level> logger;
        static std::unordered_map<int, boost::log::trivial::severity_level> const levels {
            { QtDebugMsg, boost::log::trivial::debug },
            { QtInfoMsg, boost::log::trivial::info },
            { QtWarningMsg, boost::log::trivial::warning },
            { QtCriticalMsg, boost::log::trivial::error },
            { QtFatalMsg, boost::log::trivial::fatal },
        };

        auto const it = levels.find(type);
        Q_ASSERT(it != levels.cend());
        auto const message = msg.toStdString();
        std::cout << message << "\n";
        BOOST_LOG_SEV(logger, it->second) << message;
    }

    inline void initLogging(QString const &type, QUuid const &id = {})
    {
        initBoostLog(type, id);
        qInstallMessageHandler(messageOutput);
    }
}

#endif //LOG_H
