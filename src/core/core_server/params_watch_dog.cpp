#include <config.h>
#include <plugins.h>
#include "params_watch_dog.h"

ParamsWatchDog::ParamsWatchDog(Config &config, Plugins &plugins, QObject *parent)
    : QObject{ parent }
    , _config{ config }
    , _plugins{ plugins }
{
    connect(&config, &Config::removeFinished, this, &ParamsWatchDog::onSlaveRemoved);
    connect(&config, &Config::updated, this, &ParamsWatchDog::onSlaveUpdated);
}

void ParamsWatchDog::onSlaveRemoved(QUuid const &id)
{
    for(auto const &type : _config.types())
    {
        auto const *plugin = _plugins.plugin(type);
        for(auto const &slave : _config.slaves(type))
            plugin->onWatchedSlaveRemoved(_config, id, slave);
    }
}

void ParamsWatchDog::onSlaveUpdated(QUuid const &id)
{
    for(auto const &type : _config.types())
    {
        auto const *plugin = _plugins.plugin(type);
        for(auto const &slave : _config.slaves(type))
            if (id != slave)
                plugin->onWatchedSlaveUpdated(_config, id, slave);
    }
}
