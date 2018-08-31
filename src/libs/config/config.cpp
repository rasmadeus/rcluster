#include <QDebug>
#include <QJsonArray>
#include <QNetworkInterface>
#include "config.h"

Config::Config(QObject *parent)
    : QObject{ parent }
{
}

QJsonObject Config::toJson() const
{
    QJsonArray json;
    for(auto const &slave : _slaves)
        json << slave.toJson();

    return {
        { QStringLiteral("slaves"), json },
    };
}

void Config::fromJson(QJsonObject const &json)
{
    _children.clear();
    _types.clear();
    _slaves.clear();

    for(auto const value : json.value(QStringLiteral("slaves")).toArray())
    {
        Slave slave;
        slave.fromJson(value.toObject());
        appendSlave(slave);
    }
    emit reseted();
}

QSet<QUuid> Config::descendants(QUuid const &id) const
{
    QSet<QUuid> res;
    for(auto const &child : children(id))
    {
        res << child;
        for(auto const &descendant : descendants(child))
            res << descendant;
    }
    return res;
}

QSet<QUuid> Config::localComputers() const
{
    QSet<QUuid> res;
    auto const hosts = QNetworkInterface::allAddresses();

    for(auto const &id : slaves(QStringLiteral("COMPUTER")))
    {
        auto const ip = _slaves[id].param(QStringLiteral("ip")).toString();
        if (std::any_of(hosts.cbegin(), hosts.cend(), [&ip](auto const &address){ return address.isEqual(QHostAddress{ ip }); }))
            res << id;
    }

    return res;
}

bool Config::isLocal(QUuid const &id) const
{
    auto computers = localComputers();
    if (computers.contains(id))
        return true;

    return std::any_of(computers.cbegin(), computers.cend(), [&id, this](auto const &item){
        return this->descendants(item).contains(id);
    });
}

QUuid Config::parent(QUuid const &id, QString const &parentType) const
{
    auto const slave = _slaves.value(id);
    if (slave.parent().isNull())
        return {};

    auto parent = _slaves.value(slave.parent());
    if (parent.type() == parentType)
        return parent.id();

    return this->parent(parent.id(), parentType);
}

QVector<QUuid> Config::listeners(QUuid const &id) const
{
    QVector<QUuid> res;
    for(auto const &slave : _slaves)
    {
        if (slave.id() == id)
            continue;

        if (slave.containsSlaveParams(id))
            res << slave.id();
    }
    return  res;
}

void Config::append(Slave const &slave)
{
    if (appendSlave(slave))
        emit appended(slave.id());
}

bool Config::appendSlave(Slave const &slave)
{
    if (_slaves.contains(slave.id()))
    {
        qWarning() << "Failed to append slave" << slave.id() << "due to one exists already.";
        return false;
    }

    _slaves[slave.id()] = slave;
    _children[slave.parent()] << slave.id();
    _types[slave.type()] << slave.id();
    return true;
}

void Config::remove(QUuid const &id)
{
    if (!_slaves.contains(id))
    {
        qWarning() << "Failed to remove slave" << id << "due to one doesn't exist.";
        return;
    }

    removeSlave(id);
    emit removeFinished(id);
}

void Config::removeSlave(QUuid const &id)
{
    auto const children = _children[id];
    for(auto const &child : children)
        removeSlave(child);

    Q_ASSERT(_children.remove(id) == 1);
    Q_ASSERT(_children[_slaves[id].parent()].remove(id));
    Q_ASSERT(_types[_slaves[id].type()].remove(id));
    Q_ASSERT(_slaves.remove(id) == 1);

    for(auto &slave : _slaves)
    {
        if (slave.removeSlaveParam(id))
            emit updated(slave.id());
    }

    emit removed(id);
}

void Config::enable(QUuid const &id)
{
    if (!_slaves.contains(id))
    {
        qWarning() << "Failed to enable slave" << id << "due to one doesn't exist.";
        return;
    }

    if (_slaves[id].enabled())
    {
        qWarning() << "Failed to enable slave" << id << "due to one is enabled already.";
        return;
    }

    enableFromTop(id);
    enableToBottom(id);
    emit enableFinished(id);
}

void Config::enableFromTop(QUuid const &id)
{
    if (!id.isNull())
    {
        auto &slave = _slaves[id];
        if (!slave.enabled())
        {
            enableFromTop(slave.parent());
            slave.enable();
            emit enabled(id);
        }
    }
}

void Config::enableToBottom(QUuid const &id)
{
    for(auto const &child : _children[id])
    {
        auto &slave = _slaves[child];
        Q_ASSERT(slave.disabled());
        slave.enable();
        emit enabled(child);

        enableToBottom(child);
    }
}

void Config::disable(QUuid const &id)
{
    if (!_slaves.contains(id))
    {
        qWarning() << "Failed to disable slave" << id << "due to one doesn't exist.";
        return;
    }

    if (_slaves[id].disabled())
    {
        qWarning() << "Failed to disable slave" << id << "due to one is disabled already.";
        return;
    }

    disableFromBottom(id);
    emit disableFinished(id);
}

void Config::rename(QUuid const &id, QString const &name)
{
    if (!_slaves.contains(id))
    {
        qWarning() << "Failed to rename slave" << id << "due to one doesn't exist.";
        return;
    }

    auto &slave = _slaves[id];
    if (slave.name() == name)
    {
        qWarning() << "Failed to rename slave" << id << "due to one has actual name.";
        return;
    }

    slave.setName(name);
    emit renamed(id);
}

void Config::update(QUuid const &id, QVariantHash const &params, SlaveAsParams const &slaveAsParams)
{
    if (!_slaves.contains(id))
    {
        qWarning() << "Failed to update slave" << id << "due to one doesn't exist.";
        return;
    }

    auto &slave = _slaves[id];
    slave.setParams(params);
    slave.setSlaveAsParams(slaveAsParams);

    emit updated(id);
}

void Config::setProcessState(QUuid const &id, QProcess::ProcessState state)
{
    if (!_slaves.contains(id))
    {
        qWarning() << "Failed to update slave" << id << "due to one doesn't exist.";
        return;
    }

    auto &slave = _slaves[id];
    slave.setProcessState(state);
    emit processStateChanged(id);
}

void Config::setRuntimeParam(QUuid const &id, QString const &key, QVariant const &param)
{
    if (!_slaves.contains(id))
    {
        qWarning() << "Failed to set runtime param for slave" << id << "due to one doesn't exist.";
        return;
    }
    auto &slave = _slaves[id];
    slave.setRuntimeParam(key, param);
    emit runtimeParamChanged(id, key);
}

void Config::disableFromBottom(QUuid const &id)
{
    for(auto const &child : _children[id])
        disableFromBottom(child);

    auto &slave = _slaves[id];
    if (slave.enabled())
    {
        slave.disable();
        emit disabled(id);
    }
}
