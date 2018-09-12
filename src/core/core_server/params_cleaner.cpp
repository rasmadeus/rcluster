#include <config.h>
#include <plugins.h>
#include "params_cleaner.h"

ParamsCleaner::ParamsCleaner(Config &config, Plugins &plugins, QObject *parent)
    : QObject{ parent }
    , _config{ config }
    , _plugins{ plugins }
{
    connect(&config, &Config::removeFinished, this, &ParamsCleaner::onSlaveRemoved);
}

void ParamsCleaner::onSlaveRemoved(QUuid const &id)
{
    for(auto const &type : _config.types())
    {
        auto const *plugin = _plugins.plugin(type);
        for(auto const &slave : _config.slaves(type))
            plugin->clearParams(_config, id, slave);
    }
}
