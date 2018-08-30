#include <config.h>
#include <plugins.h>
#include <storage.h>
#include "config_storage.h"

ConfigStorage::ConfigStorage(Config &config, Plugins &plugins, QObject *parent)
    : QObject{ parent }
    , _config{ config }
    , _plugins{ plugins }
    , _storage{ Storage::make(Storage::Type::FileStorage, { { QStringLiteral("path"), rcluster::pathToFileConfig() }, }) }
{
    read();
    clean();
    save();
    watch();
}

void ConfigStorage::read()
{
    _storage->restore(_config);
}

void ConfigStorage::clean()
{
    for(auto const &id : _config.slaves())
    {
        if (_plugins.contains(_config.slave(id).type()))
            _config.update(id, QProcess::NotRunning);
        else
            _config.remove(id);
    }
}

void ConfigStorage::save()
{
    _storage->store(_config);
}

void ConfigStorage::watch()
{
    connect(&_config, &Config::appended, this, &ConfigStorage::save);
    connect(&_config, &Config::removeFinished, this, &ConfigStorage::save);
    connect(&_config, &Config::renamed, this, &ConfigStorage::save);
    connect(&_config, &Config::enableFinished, this, &ConfigStorage::save);
    connect(&_config, &Config::disableFinished, this, &ConfigStorage::save);
    connect(&_config, &Config::updated, this, &ConfigStorage::save);
    connect(&_config, &Config::runtimeParamChanged, this, &ConfigStorage::save);
}
