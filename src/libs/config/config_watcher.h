#ifndef CONFIG_WATCHER_H
#define CONFIG_WATCHER_H

#include <message_router.h>
#include "config_global.h"

class Config;
class Message;

class CONFIG_SHARED_EXPORT ConfigWatcher : public MessageRouter
{
public:
    explicit ConfigWatcher(Config &config);

private:
    void onReset(Message const &message);

    void onAppendSlave(Message const &message);
    void onRemoveSlave(Message const &message);
    void onRenameSlave(Message const &message);
    void onEnableSlave(Message const &message);
    void onDisableSlave(Message const &message);
    void onUpdateSlave(Message const &message);
    void onProcess(Message const &message);

private:
    Config &_config;
};

#endif // CONFIG_WACHER_H
