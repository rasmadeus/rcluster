#include <message.h>
#include "config.h"
#include "config_watcher.h"

ConfigWatcher::ConfigWatcher(Config &config)
    : _config{ config }
{
    handle(QStringLiteral("CONFIG"), std::bind(&ConfigWatcher::onReset, this, std::placeholders::_1));
    handle(QStringLiteral("APPEND"), std::bind(&ConfigWatcher::onAppendNode, this, std::placeholders::_1));
    handle(QStringLiteral("REMOVE"), std::bind(&ConfigWatcher::onRemoveNode, this, std::placeholders::_1));
    handle(QStringLiteral("RENAME"), std::bind(&ConfigWatcher::onRenameNode, this, std::placeholders::_1));
    handle(QStringLiteral("ENABLE"), std::bind(&ConfigWatcher::onEnableNode, this, std::placeholders::_1));
    handle(QStringLiteral("DISABLE"), std::bind(&ConfigWatcher::onDisableNode, this, std::placeholders::_1));
    handle(QStringLiteral("UPDATE"), std::bind(&ConfigWatcher::onUpdateNode, this, std::placeholders::_1));
    handle(QStringLiteral("PROCESS"), std::bind(&ConfigWatcher::onProcess, this, std::placeholders::_1));
    handle(QStringLiteral("RUNTIME"), std::bind(&ConfigWatcher::onRuntime, this, std::placeholders::_1));
}

void ConfigWatcher::onReset(Message const &message)
{
    _config.fromJson(
        message.param(QStringLiteral("config")).toJsonObject()
    );
}

void ConfigWatcher::onAppendNode(Message const &message)
{
    Node node;
    node.fromJson(message.param(QStringLiteral("node")).toJsonObject());
    _config.append(node);
}

void ConfigWatcher::onRemoveNode(Message const &message)
{
    _config.remove(
        message.param(QStringLiteral("node")).toUuid()
    );
}

void ConfigWatcher::onRenameNode(Message const &message)
{
    _config.rename(
        message.param(QStringLiteral("node")).toUuid(),
        message.param(QStringLiteral("name")).toString()
    );
}

void ConfigWatcher::onEnableNode(Message const &message)
{
    _config.enable(
        message.param(QStringLiteral("node")).toUuid()
    );
}

void ConfigWatcher::onDisableNode(Message const &message)
{
    _config.disable(
        message.param(QStringLiteral("node")).toUuid()
    );
}

void ConfigWatcher::onUpdateNode(Message const &message)
{
    _config.update(
        message.param(QStringLiteral("node")).toUuid(),
        message.param(QStringLiteral("params")).value<QVariantHash>()
    );
}

void ConfigWatcher::onProcess(Message const &message)
{
    _config.setProcessState(
        message.param(QStringLiteral("node")).toUuid(),
        message.param(QStringLiteral("process_state")).value<QProcess::ProcessState>()
    );
}

void ConfigWatcher::onRuntime(Message const &message)
{
    _config.setRuntimeParam(
        message.param(QStringLiteral("node")).toUuid(),
        message.param(QStringLiteral("key")).toString(),
        message.param(QStringLiteral("value"))
    );
}
