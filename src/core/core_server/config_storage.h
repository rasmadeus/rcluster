#ifndef CONFIG_STORAGE_H
#define CONFIG_STORAGE_H

#include <QObject>
#include <globals.h>
#include <storage.h>

class Config;
class Plugins;

class ConfigStorage : public QObject
{
    Q_OBJECT

public:
    explicit ConfigStorage(Config &config, Plugins &plugins, QObject *parent = nullptr);

private:
    void read();
    void clean();
    void save();
    void watch();

private:
    Config &_config;
    Plugins &_plugins;
    std::unique_ptr<Storage> _storage;

};

#endif // CONFIG_STORAGE_H
