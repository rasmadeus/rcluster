#ifndef SLAVE_CONTROLLER_H
#define SLAVE_CONTROLLER_H

#include <QUuid>
#include "plugin_global.h"

class Config;
class CoreClientSocket;
class Message;
class Plugin;

class PLUGIN_SHARED_EXPORT SlaveController
{
public:
    SlaveController(Config const &config, Plugin const &plugin, CoreClientSocket &socket);
    virtual ~SlaveController() = default;

public:
    virtual void init() = 0;
    virtual void onMessage(Message const &message) = 0;

protected:
    Config const &_config;
    Plugin const &_plugin;
    CoreClientSocket &_socket;
};

#endif // SLAVE_CONTROLLER_H
