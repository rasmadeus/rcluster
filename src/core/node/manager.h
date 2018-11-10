#ifndef MANAGER_H
#define MANAGER_H

#include <memory>
#include <QObject>
#include <config.h>
#include <corebus.h>
#include <config_watcher.h>
#include <message.h>
#include <node_controller.h>
#include "args.h"

class Plugin;

class Manager : public QObject
{
    Q_OBJECT

public:
    explicit Manager(Args const &args, QObject *parent = nullptr);

public:
    void start();

private:
    void restoreSettings();
    void onReseted();
    void onUpdated(QUuid const &id);
    void onReady(Message const &message);

private:
    Args _args;
    Plugin *_plugin;
    Config _config;
    ConfigWatcher _configWatcher;
    Corebus _corebus;
    std::unique_ptr<NodeController> _controller;

};

#endif // MANAGER_H
