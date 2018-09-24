#ifndef EXPERIMENT_CENTER_H
#define EXPERIMENT_CENTER_H

#include <QObject>
#include <QUuid>

class Config;
class Corebus;
class Slave;

class ExperimentCenter : public QObject
{
    Q_OBJECT

public:
    explicit ExperimentCenter(Config const &config, Corebus &corebus, QObject &parent);

public:
    void onSetup(Slave const &slave);
    void start();
    void stop();

private:
    Config const &_config;
    Corebus &_corebus;
    QUuid _mediaPlayer;
};

#endif // EXPERIMENT_CENTER_H
