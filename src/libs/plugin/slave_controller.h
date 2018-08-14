#ifndef SLAVE_CONTROLLER_H
#define SLAVE_CONTROLLER_H

#include <QUuid>
#include "plugin_global.h"

class Config;
class Corebus;
class Message;
class Plugin;

class PLUGIN_SHARED_EXPORT SlaveController
{
public:
    virtual ~SlaveController() = default;

public:
    virtual void init() = 0;
    virtual void onMessage(Message const &message) = 0;

public:
    void setConfig(Config const &config) { _config = &config; }
    void setPlugin(Plugin const &plugin) { _plugin = &plugin; }
    void setCorebus(Corebus &corebus) { _corebus = &corebus; }

protected:
    Config const *_config{ nullptr };
    Plugin const *_plugin{ nullptr };
    Corebus *_corebus{ nullptr };
};

#endif // SLAVE_CONTROLLER_H
