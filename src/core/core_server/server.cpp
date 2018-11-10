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

    connect(&_config, &Config::appended, this, &Server::onConfigNodeAppended);
    connect(&_config, &Config::removeFinished, this, &Server::onConfigNodeRemoved);
    connect(&_config, &Config::renamed, this, &Server::onConfigNodeRenamed);
    connect(&_config, &Config::enableFinished, this, &Server::onConfigNodeEnabled);
    connect(&_config, &Config::disableFinished, this, &Server::onConfigNodeDisabled);
    connect(&_config, &Config::updated, this, &Server::onConfigNodeUpdated);
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

    for(auto const &type : _config.types())
    {
        auto const *plugin = _plugins.plugin(type);
        for(auto const &id : _config.nodes(type))
        {
            if (plugin->isListener(_config, message.from(), id))
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

void Server::onExit([[maybe_unused]] Message const &message)
{
    send(QStringLiteral("EXIT"));
    qApp->quit();
}

void Server::onConfigReseted()
{
    send(QStringLiteral("CONFIG"), {
        { QStringLiteral("config"), _config.toJson() },
    });
}

void Server::onConfigNodeAppended(QUuid const &node)
{
    send(QStringLiteral("APPEND"), {
        { QStringLiteral("node"), _config.node(node).toJson() },
    });
}

void Server::onConfigNodeRemoved(QUuid const &node)
{
    send(QStringLiteral("REMOVE"), {
        { QStringLiteral("node"), node },
    });

    for(auto const &type : _config.types())
    {
        auto const *plugin = _plugins.plugin(type);
        for(auto const &id : _config.nodes(type))
            plugin->onNodeRemoved(_config, node, id);
    }
}

void Server::onConfigNodeRenamed(QUuid const &node)
{
    send(QStringLiteral("RENAME"), {
        { QStringLiteral("node"), node },
        { QStringLiteral("name"), _config.node(node).name() },
    });
}

void Server::onConfigNodeEnabled(QUuid const &node)
{
    send(QStringLiteral("ENABLE"), {
        { QStringLiteral("node"), node },
    });
}

void Server::onConfigNodeDisabled(QUuid const &node)
{
    send(QStringLiteral("DISABLE"), {
        { QStringLiteral("node"), node },
    });
}

void Server::onConfigNodeUpdated(QUuid const &node)
{
    auto const nodeObject = _config.node(node);

    send(QStringLiteral("UPDATE"), {
        { QStringLiteral("node"), node },
        { QStringLiteral("params"), nodeObject.params() },
    });

    for (auto const &type : _config.types())
    {
        auto const *plugin = _plugins.plugin(type);
        for (auto const &id : _config.nodes(type))
            if (node != id)
                plugin->onNodeUpdated(_config, node, id);
    }
}

void Server::onConfigProcessStateChanged(QUuid const &node)
{
    send(QStringLiteral("PROCESS"), {
        { QStringLiteral("node"), node },
        { QStringLiteral("process_state"), _config.node(node).processState() },
    });
}

void Server::onConfigRuntime(QUuid const &node, QString const &key)
{
    send(QStringLiteral("RUNTIME"), {
        { QStringLiteral("node"), node },
        { QStringLiteral("key"), key },
        { QStringLiteral("value"), _config.node(node).runtimeParam(key) },
    });
}
