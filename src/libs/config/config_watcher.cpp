#include <message.h>
#include "config.h"
#include "config_watcher.h"

ConfigWatcher::ConfigWatcher(Config &config)
    : _config{ config }
{
    handle(QStringLiteral("CONFIG"), std::bind(&ConfigWatcher::onReset, this, std::placeholders::_1));
    handle(QStringLiteral("APPEND"), std::bind(&ConfigWatcher::onAppendSlave, this, std::placeholders::_1));
    handle(QStringLiteral("REMOVE"), std::bind(&ConfigWatcher::onRemoveSlave, this, std::placeholders::_1));
    handle(QStringLiteral("RENAME"), std::bind(&ConfigWatcher::onRenameSlave, this, std::placeholders::_1));
    handle(QStringLiteral("ENABLE"), std::bind(&ConfigWatcher::onEnableSlave, this, std::placeholders::_1));
    handle(QStringLiteral("DISABLE"), std::bind(&ConfigWatcher::onDisableSlave, this, std::placeholders::_1));
    handle(QStringLiteral("UPDATE"), std::bind(&ConfigWatcher::onUpdateSlave, this, std::placeholders::_1));
    handle(QStringLiteral("PROCESS"), std::bind(&ConfigWatcher::onProcess, this, std::placeholders::_1));
}

void ConfigWatcher::onReset(Message const &message)
{
    _config.fromJson(
        message.param(QStringLiteral("config")).toJsonObject()
    );
}

void ConfigWatcher::onAppendSlave(Message const &message)
{
    Slave slave;
    slave.fromJson(message.param(QStringLiteral("slave")).toJsonObject());
    _config.append(slave);
}

void ConfigWatcher::onRemoveSlave(Message const &message)
{
    _config.remove(
        message.param(QStringLiteral("slave")).toUuid()
    );
}

void ConfigWatcher::onRenameSlave(Message const &message)
{
    _config.rename(
        message.param(QStringLiteral("slave")).toUuid(),
        message.param(QStringLiteral("name")).toString()
    );
}

void ConfigWatcher::onEnableSlave(Message const &message)
{
    _config.enable(
        message.param(QStringLiteral("slave")).toUuid()
    );
}

void ConfigWatcher::onDisableSlave(Message const &message)
{
    _config.disable(
        message.param(QStringLiteral("slave")).toUuid()
    );
}

void ConfigWatcher::onUpdateSlave(Message const &message)
{
    _config.update(
        message.param(QStringLiteral("slave")).toUuid(),
        message.param(QStringLiteral("params")).value<QVariantHash>(),
        SlaveIds{ message.param(QStringLiteral("events")).toJsonArray() }.ids()
    );
}

void ConfigWatcher::onProcess(Message const &message)
{
    _config.update(
        message.param(QStringLiteral("slave")).toUuid(),
        message.param(QStringLiteral("process_state")).value<QProcess::ProcessState>()
    );
}
