#ifndef PCH_H
#define PCH_H

#include <signal.h>

#if defined __cplusplus
    #include <chrono>
    #include <fstream>

    #include <boost/log/core.hpp>
    #include <boost/filesystem.hpp>
    #include <boost/log/trivial.hpp>
    #include <boost/log/expressions.hpp>
    #include <boost/log/sinks/text_file_backend.hpp>
    #include <boost/log/utility/setup/file.hpp>
    #include <boost/log/utility/setup/common_attributes.hpp>
    #include <boost/log/sources/severity_logger.hpp>
    #include <boost/log/sources/record_ostream.hpp>
    #include <boost/stacktrace.hpp>

    #include <QtCore>
    #include <QtWidgets>
    #include <QtNetwork>
#endif

#endif // PCH_H
