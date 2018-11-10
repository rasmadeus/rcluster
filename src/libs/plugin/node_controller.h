#ifndef NODE_CONTROLLER_H
#define NODE_CONTROLLER_H

#include <QUuid>
#include <message_router.h>
#include "plugin_global.h"

class Config;
class Corebus;
class Message;
class Plugin;
class Node;

class PLUGIN_SHARED_EXPORT NodeController
{
public:
    NodeController(Config const &config, Plugin const &plugin, Corebus &corebus);
    virtual ~NodeController() = default;

public:
    virtual void onSetup(Node const &slave) = 0;
    virtual void onMessage(Message const &message) { _router.route(message); }
    virtual void restoreSettings() {}

protected:
    Config const &_config;
    Plugin const &_plugin;
    Corebus &_corebus;
    MessageRouter _router;
};

#endif // NODE_CONTROLLER_H
