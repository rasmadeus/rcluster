#ifndef PARAMS_WATCH_DOG_H
#define PARAMS_WATCH_DOG_H

#include <QObject>
class Config;
class Plugins;

class ParamsWatchDog : public QObject
{
    Q_OBJECT

public:
    explicit ParamsWatchDog(Config &config, Plugins &plugins, QObject *parent = nullptr);

private:
    void onSlaveRemoved(QUuid const &id);
    void onSlaveUpdated(QUuid const &id);

private:
    Config &_config;
    Plugins &_plugins;
};

#endif // PARAMS_WATCH_DOG_H
