#include <config.h>
#include <plugins.h>
#include "supervisors.h"

Supervisors::Supervisors(Config &config, Plugins &plugins, QObject *parent)
    : QObject{ parent }
    , _config{ config }
    , _plugins{ plugins }
{
    connect(&config, &Config::reseted, this, &Supervisors::onReseted);
    connect(&config, &Config::appended, this, &Supervisors::onAppended);
    connect(&config, &Config::removed, this, &Supervisors::onRemoved);
    connect(&config, &Config::enabled, this, &Supervisors::onEnabled);
    connect(&config, &Config::disabled, this, &Supervisors::onDisabled);
    connect(&config, &Config::updated, this, &Supervisors::onUpdated);
}

void Supervisors::setCoreAddress(QString const &host, QString const &port)
{
    if (_host == host && _port == port)
        return;

    _host = host;
    _port = port;

    if (!_processes.isEmpty())
        stop();
}

void Supervisors::start(QUuid const &id)
{
    auto const slave = _config.slave(id);
    if (slave.disabled())
        return;

    auto const plugin = _plugins.plugin(slave.type());
    if (!plugin->hasProcess())
        return;

    auto supervisor = std::make_shared<Supervisor>(plugin, id, _host, _port, *this);
    _processes[id] = supervisor;
    connect(supervisor.get(), &Supervisor::processStateChanged, this, &Supervisors::processStateChanged);
    supervisor->start();
}

void Supervisors::onReseted()
{
    auto computers = _config.localComputers();

    if (computers.isEmpty())
        stop();

    QSet<QUuid> expectedSlaves;
    for(auto const &computer : computers)
    {
        for(auto const &slave : _config.descendants(computer))
            expectedSlaves << slave;
        expectedSlaves << computer;
    }

    for(auto const &id : _processes.keys().toSet() - expectedSlaves)
        _processes.remove(id);

    for(auto const &id : expectedSlaves - _processes.keys().toSet())
        start(id);
}

void Supervisors::onAppended(QUuid const &id)
{
    if (_config.isLocal(id) && !_processes.contains(id))
        start(id);
}

void Supervisors::onRemoved(QUuid const &id)
{
    _processes.remove(id);
}

void Supervisors::onEnabled(QUuid const &id)
{
    onAppended(id);
}

void Supervisors::onDisabled(QUuid const &id)
{
    onRemoved(id);
}

void Supervisors::onUpdated(QUuid const &id)
{
    auto const slave = _config.slave(id);
    if (slave.type() == QStringLiteral("COMPUTER"))
        onReseted();
}
