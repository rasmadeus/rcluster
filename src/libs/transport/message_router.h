#ifndef MESSAGE_ROUTER_H
#define MESSAGE_ROUTER_H

#include <functional>
#include <vector>
#include <QHash>
#include "transport_global.h"

class Message;

class TRANSPORT_SHARED_EXPORT MessageRouter
{
public:
    void handle(QString const &action, std::function<void(Message const &message)> const &handler);
    bool route(Message const &messsage);

private:
    QHash<QString, std::vector<std::function<void(Message const &message)>>> _handlers;
};

#endif // MESSAGE_ROUTER_H
