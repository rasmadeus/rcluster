#ifndef LOG_H
#define LOG_H

#include <QUuid>
#include <globals.h>
#include "utils_global.h"

class UTILS_SHARED_EXPORT Log
{
public:
    static QString path(QString const &type, QUuid const &id);
    void init(QString const &type, QUuid const &id = {});

private:
    void initBoostLogging(QString const &type, QUuid const &id);
    void handleQtLogging(QtMsgType type, QMessageLogContext const &context, QString const &msg);
};

#endif // LOG_H
