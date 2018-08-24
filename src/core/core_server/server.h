#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <unordered_map>
#include <QTcpServer>
#include <config_watcher.h>
#include <qt_types_hash.h>
#include <message.h>
#include <message_router.h>

#include "client.h"

class Config;

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(quint16 port, Config &config, QObject *parent = nullptr);

private:
    void appendClient();
    void removeClient();
    void sendConfig(Client &client);
    void send(QString const &action, QVariantHash const &params = {});

private:
    void onMessage(Message const &message);
    void onRegister(Message const &message);
    void onExit(Message const &message);
    void notifyListeners(Message const &message);

private:
    void onConfigReseted();

    void onConfigSlaveAppended(QUuid const &slave);
    void onConfigSlaveRemoved(QUuid const &slave);
    void onConfigSlaveRenamed(QUuid const &slave);
    void onConfigSlaveEnabled(QUuid const &slave);
    void onConfigSlaveDisabled(QUuid const &slave);
    void onConfigSlaveUpdated(QUuid const &slave);
    void onConfigProcessStateChanged(QUuid const &slave);
    void onConfigRuntime(QUuid const &slave, QString const &key);

private:
    Config &_config;
    QTcpServer _server;
    std::vector<std::unique_ptr<Client>> _clients;
    std::unordered_map<QUuid, Client*, QUuidHash> _registeredClients;
    ConfigWatcher _messageRouter;
};

#endif // SERVER_H
