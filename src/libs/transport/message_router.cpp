#include "message.h"
#include "message_router.h"

void MessageRouter::handle(QString const &action, std::function<void(Message const &message)> const &handler)
{
    _handlers[action].push_back(handler);
}

bool MessageRouter::route(Message const &messsage)
{
    auto handlers = _handlers.find(messsage.action());
    if (handlers != _handlers.end())
    {
        for(auto &handler : *handlers)
            handler(messsage);

        return true;
    }
    return false;
}
