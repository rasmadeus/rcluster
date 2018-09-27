#ifndef SLAVE_CONTROLLER_H
#define SLAVE_CONTROLLER_H

#include <QUuid>
#include <message_router.h>
#include "plugin_global.h"

class Config;
class Corebus;
class Message;
class Plugin;
class Slave;

class PLUGIN_SHARED_EXPORT SlaveController
{
public:
    SlaveController(Config const &config, Plugin const &plugin, Corebus &corebus);
    virtual ~SlaveController() = default;

public:
    virtual void onSetup(Slave const &slave) = 0;
    virtual void onMessage(Message const &message) { _router.route(message); }
    virtual void restoreSettings() {}

protected:
    Config const &_config;
    Plugin const &_plugin;
    Corebus &_corebus;
    MessageRouter _router;
};

#endif // SLAVE_CONTROLLER_H
