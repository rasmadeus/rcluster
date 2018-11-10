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

    void onAppendNode(Message const &message);
    void onRemoveNode(Message const &message);
    void onRenameNode(Message const &message);
    void onEnableNode(Message const &message);
    void onDisableNode(Message const &message);
    void onUpdateNode(Message const &message);
    void onProcess(Message const &message);
    void onRuntime(Message const &message);

private:
    Config &_config;
};

#endif // CONFIG_WACHER_H
