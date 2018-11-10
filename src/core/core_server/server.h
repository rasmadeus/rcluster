#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <unordered_map>
#include <QTcpServer>
#include <config_watcher.h>
#include <hash_functions.h>
#include <message.h>
#include <message_router.h>

#include "client.h"

class Config;
class Plugins;

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(quint16 port, Config &config, Plugins &plugins, QObject *parent = nullptr);

private:
    void appendClient();
    void removeClient();
    void sendConfig(Client &client);
    void send(QString const &action, QVariantHash const &params = {});

private:
    void onMessage(Message const &message);
    void onRegister(Message const &message);
    void onExit(Message const &message);

private:
    void onConfigReseted();

    void onConfigNodeAppended(QUuid const &node);
    void onConfigNodeRemoved(QUuid const &node);
    void onConfigNodeRenamed(QUuid const &node);
    void onConfigNodeEnabled(QUuid const &node);
    void onConfigNodeDisabled(QUuid const &node);
    void onConfigNodeUpdated(QUuid const &node);
    void onConfigProcessStateChanged(QUuid const &node);
    void onConfigRuntime(QUuid const &node, QString const &key);

private:
    Config &_config;
    Plugins &_plugins;
    QTcpServer _server;
    std::vector<std::unique_ptr<Client>> _clients;
    std::unordered_map<QUuid, Client*, QUuidHash> _registeredClients;
    ConfigWatcher _messageRouter;
};

#endif // SERVER_H
