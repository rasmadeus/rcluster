#ifndef SUPERVISORS_H
#define SUPERVISORS_H

#include <memory>
#include <QObject>
#include "supervisor.h"

class Config;
class Plugins;

class Supervisors : public QObject
{
    Q_OBJECT

public:
    explicit Supervisors(Config &config, Plugins &plugins, QObject *parent = nullptr);

public:
    void setCoreAddress(QString const &host, QString const &port);

private:
    void start(QUuid const &id);    
    void stop() { _processes.clear(); }

private:
    void onReseted();
    void onAppended(QUuid const &id);
    void onRemoved(QUuid const &id);
    void onEnabled(QUuid const &id);
    void onDisabled(QUuid const &id);
    void onUpdated(QUuid const &id);

private:
    QHash<QUuid, std::shared_ptr<Supervisor>> _processes;
    Config &_config;
    Plugins &_plugins;
    QString _host;
    QString _port;
};

#endif // SUPERVISORS_H
