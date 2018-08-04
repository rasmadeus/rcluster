#include <config.h>
#include <storage.h>
#include "config_storage.h"

ConfigStorage::ConfigStorage(Config &config, QObject *parent)
    : QObject{ parent }
    , _config{ config }
    , _storage{ Storage::make(Storage::Type::FileStorage, { { QStringLiteral("path"), rcluster::pathToFileConfig() }, }) }
{
    _storage->restore(_config);

    connect(&_config, &Config::appended, this, &ConfigStorage::save);
    connect(&_config, &Config::removeFinished, this, &ConfigStorage::save);
    connect(&_config, &Config::renamed, this, &ConfigStorage::save);
    connect(&_config, &Config::enableFinished, this, &ConfigStorage::save);
    connect(&_config, &Config::disableFinished, this, &ConfigStorage::save);
    connect(&_config, &Config::updated, this, &ConfigStorage::save);
}

void ConfigStorage::save()
{
    _storage->store(_config);
}
