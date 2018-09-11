#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QVariantHash>
#include "utils_global.h"

class UTILS_SHARED_EXPORT Device : public QObject
{
    Q_OBJECT

public:
    explicit Device(QObject *parent = nullptr);

public:
    virtual void start(QVariantHash const &params) = 0;
    virtual void stop() = 0;

protected:
    void logError(QString const &what);

signals:
    void started();
    void stopped();
    void error(QString const &what);
};

#endif // DEVICE_H