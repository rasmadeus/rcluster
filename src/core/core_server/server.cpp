#include <QApplication>
#include <QTcpSocket>
#include <config.h>
#include <plugins.h>
#include "server.h"

Server::Server(quint16 port, Config &config, Plugins &plugins, QObject *parent)
    : QObject{ parent }
    , _config{ config }
    , _plugins{ plugins }
    , _messageRouter{ config }
{
    _messageRouter.handle(QStringLiteral("REGISTER"), std::bind(&Server::onRegister, this, std::placeholders::_1));
    _messageRouter.handle(QStringLiteral("EXIT"), std::bind(&Server::onExit, this, std::placeholders::_1));

    connect(&_config, &Config::reseted, this, &Server::onConfigReseted);

    connect(&_config, &Config::appended, this, &Server::onConfigSlaveAppended);
    connect(&_config, &Config::removeFinished, this, &Server::onConfigSlaveRemoved);
    connect(&_config, &Config::renamed, this, &Server::onConfigSlaveRenamed);
    connect(&_config, &Config::enableFinished, this, &Server::onConfigSlaveEnabled);
    connect(&_config, &Config::disableFinished, this, &Server::onConfigSlaveDisabled);
    connect(&_config, &Config::updated, this, &Server::onConfigSlaveUpdated);
    connect(&_config, &Config::processStateChanged, this, &Server::onConfigProcessStateChanged);
    connect(&_config, &Config::runtimeParamChanged, this, &Server::onConfigRuntime);

    connect(&_server, &QTcpServer::newConnection, this, &Server::appendClient);
    _server.listen(QHostAddress::Any, port);
}

void Server::appendClient()
{
    while(_server.hasPendingConnections())
    {
        auto socket = _server.nextPendingConnection();
        _clients.emplace_back( std::make_unique<Client>(*socket));
        connect(_clients.back().get(), &Client::disconnected, this, &Server::removeClient);
        connect(_clients.back().get(), &Client::ready, this, &Server::onMessage);
        sendConfig(*_clients.back().get());
    }
}

void Server::removeClient()
{
    auto client = static_cast<Client*>(sender());

    {
        auto it = std::find_if(_registeredClients.begin(), _registeredClients.end(), [client](auto const &item){ return client == item.second; });
        if (it != _registeredClients.end())
            _registeredClients.erase(it);
    }

    {
        auto it = std::find_if(_clients.begin(), _clients.end(), [client](auto const &item){ return client == item.get(); });
        if (it != _clients.end())
            _clients.erase(it);
    }
}

void Server::sendConfig(Client &client)
{
    client.send({ QStringLiteral("CONFIG"), client.id().toString(), QStringLiteral("core"), { { QStringLiteral("config"), _config.toJson() } }, });
}

void Server::send(QString const &action, QVariantHash const &params)
{
    for(auto &client : _clients)
        client->send({ action, client->id().toString(), QStringLiteral("core"), params });
}

void Server::onMessage(Message const &message)
{
    if (message.to() == QStringLiteral("core"))
    {
        _messageRouter.route(message);
    }
    else
    {
        auto it = _registeredClients.find(message.toId());
        if (it == _registeredClients.end())
            qCritical() << "Failed to delivery message to unknown slave.";
        else
            it->second->send(message);
    }

    auto const messageSource = message.fromId();
    for(auto const &type : _config.types())
    {
        auto const *plugin = _plugins.plugin(type);
        for(auto const &id : _config.slaves(type))
        {
            if (plugin->isListener(_config, messageSource, id))
            {
                auto it = _registeredClients.find(id);
                if (it != _registeredClients.end())
                    it->second->send(message);
            }
        }
    }
}

void Server::onRegister(Message const &message)
{
    auto slave = static_cast<Client*>(sender());
    auto const it = std::find_if(_registeredClients.cbegin(), _registeredClients.cend(), [slave](auto const &item){ return item.second == slave; });

    if (it != _registeredClients.cend())
    {
        qWarning() << "Slave has been already registered.";
    }
    else
    {
        slave->setId(message.fromId());
        _registeredClients[slave->id()] = slave;
    }
}

void Server::onExit(Message const &message)
{
    Q_UNUSED(message)
    send(QStringLiteral("EXIT"));
    qApp->quit();
}

void Server::onConfigReseted()
{
    send(QStringLiteral("CONFIG"), {
        { QStringLiteral("config"), _config.toJson() },
    });
}

void Server::onConfigSlaveAppended(QUuid const &slave)
{
    send(QStringLiteral("APPEND"), {
        { QStringLiteral("slave"), _config.slave(slave).toJson() },
    });
}

void Server::onConfigSlaveRemoved(QUuid const &slave)
{
    send(QStringLiteral("REMOVE"), {
        { QStringLiteral("slave"), slave },
    });

    for(auto const &type : _config.types())
    {
        auto const *plugin = _plugins.plugin(type);
        for(auto const &id : _config.slaves(type))
            plugin->onWatchedSlaveRemoved(_config, slave, id);
    }
}

void Server::onConfigSlaveRenamed(QUuid const &slave)
{
    send(QStringLiteral("RENAME"), {
        { QStringLiteral("slave"), slave },
        { QStringLiteral("name"), _config.slave(slave).name() },
    });
}

void Server::onConfigSlaveEnabled(QUuid const &slave)
{
    send(QStringLiteral("ENABLE"), {
        { QStringLiteral("slave"), slave },
    });
}

void Server::onConfigSlaveDisabled(QUuid const &slave)
{
    send(QStringLiteral("DISABLE"), {
        { QStringLiteral("slave"), slave },
    });
}

void Server::onConfigSlaveUpdated(QUuid const &slave)
{
    auto const slaveObject = _config.slave(slave);

    send(QStringLiteral("UPDATE"), {
        { QStringLiteral("slave"), slave },
        { QStringLiteral("params"), slaveObject.params() },
    });
}

void Server::onConfigProcessStateChanged(QUuid const &slave)
{
    send(QStringLiteral("PROCESS"), {
        { QStringLiteral("slave"), slave },
        { QStringLiteral("process_state"), _config.slave(slave).processState() },
    });
}

void Server::onConfigRuntime(QUuid const &slave, QString const &key)
{
    send(QStringLiteral("RUNTIME"), {
        { QStringLiteral("slave"), slave },
        { QStringLiteral("key"), key },
        { QStringLiteral("value"), _config.slave(slave).runtimeParam(key) },
    });
}
