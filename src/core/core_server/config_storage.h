#ifndef CONFIG_SAVER_H
#define CONFIG_SAVER_H

#include <QObject>
#include <globals.h>
#include <storage.h>

class Config;

class ConfigStorage : public QObject
{
    Q_OBJECT
public:
    explicit ConfigStorage(Config &config, QObject *parent = nullptr);

private:
    void save();

private:
    Config &_config;
    std::unique_ptr<Storage> _storage;

};

#endif // CONFIG_SAVER_H
