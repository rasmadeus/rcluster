#ifndef PARAMS_CLEANER_H
#define PARAMS_CLEANER_H

#include <QObject>
class Config;
class Plugins;

class ParamsCleaner : public QObject
{
    Q_OBJECT

public:
    explicit ParamsCleaner(Config &config, Plugins &plugins, QObject *parent = nullptr);

private:
    void onSlaveRemoved(QUuid const &id);

private:
    Config &_config;
    Plugins &_plugins;
};

#endif // PARAMS_CLEANER_H
