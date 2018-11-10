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
    for(auto const &node : _nodes)
        json << node.toJson();

    return {
        { QStringLiteral("nodes"), json },
    };
}

void Config::fromJson(QJsonObject const &json)
{
    _children.clear();
    _types.clear();
    _nodes.clear();

    for(auto const value : json.value(QStringLiteral("nodes")).toArray())
    {
        Node node;
        node.fromJson(value.toObject());
        appendNode(node);
    }
    emit reseted();
}

QVector<QUuid> Config::descendants(QUuid const &id) const
{
    QVector<QUuid> res;
    for(auto const &child : children(id))
    {
        res << child;
        for(auto &&descendant : descendants(child))
            res << std::move(descendant);
    }
    return res;
}

QVector<QUuid> Config::descendants(QUuid const &id, QString const &type) const
{
    QVector<QUuid> res;
    for(auto const &child : children(id))
    {
        auto const node = this->node(child);
        if (node.id() != id && node.type() == type)
            res << child;

        for(auto &&descendant : descendants(child, type))
            res << std::move(descendant);
    }
    return res;
}

QVector<QUuid> Config::localComputers() const
{
    QVector<QUuid> res;
    auto const hosts = QNetworkInterface::allAddresses();

    for(auto const &id : nodes(QStringLiteral("COMPUTER")))
    {
        auto const ip = _nodes[id].param(QStringLiteral("ip")).toString();
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
    auto const node = _nodes.value(id);
    if (node.parent().isNull())
        return {};

    auto parent = _nodes.value(node.parent());
    if (parent.type() == parentType)
        return parent.id();

    return this->parent(parent.id(), parentType);
}

QUuid Config::findLocalParam(QUuid const &id, QString const &key, QVariant const &param) const
{
    auto const object = node(id);
    auto const computerId = parent(id, QStringLiteral("COMPUTER"));
    for(auto const &descendantId : descendants(computerId, object.type()))
    {
        if (id == descendantId)
            continue;

        auto const node = this->node(descendantId);

        if (node.isFake())
            continue;

        auto const nodeParam = node.param(key);
        if (!nodeParam.isValid())
            continue;

        if (nodeParam == param)
            return descendantId;
    }
    return {};
}

void Config::append(Node const &node)
{
    if (appendNode(node))
        emit appended(node.id());
}

bool Config::appendNode(Node const &node)
{
    if (_nodes.contains(node.id()))
    {
        qWarning() << "Failed to append node" << node.id() << "due to one exists already.";
        return false;
    }

    _nodes[node.id()] = node;
    _children[node.parent()] << node.id();
    _types[node.type()] << node.id();
    return true;
}

void Config::remove(QUuid const &id)
{
    if (!_nodes.contains(id))
    {
        qWarning() << "Failed to remove node" << id << "due to one doesn't exist.";
        return;
    }

    removeNode(id);
    emit removeFinished(id);
}

void Config::removeNode(QUuid const &id)
{
    auto const children = _children[id];
    for(auto const &child : children)
        removeNode(child);

    Q_ASSERT(_children.remove(id) == 1);
    Q_ASSERT(_children[_nodes[id].parent()].removeAll(id) == 1);
    Q_ASSERT(_types[_nodes[id].type()].removeAll(id) == 1);
    Q_ASSERT(_nodes.remove(id) == 1);

    emit removed(id);
}

void Config::enable(QUuid const &id)
{
    if (!_nodes.contains(id))
    {
        qWarning() << "Failed to enable node" << id << "due to one doesn't exist.";
        return;
    }

    if (_nodes[id].enabled())
    {
        qWarning() << "Failed to enable node" << id << "due to one is enabled already.";
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
        auto &node = _nodes[id];
        if (!node.enabled())
        {
            enableFromTop(node.parent());
            node.enable();
            emit enabled(id);
        }
    }
}

void Config::enableToBottom(QUuid const &id)
{
    for(auto const &child : _children[id])
    {
        auto &node = _nodes[child];
        Q_ASSERT(node.disabled());
        node.enable();
        emit enabled(child);

        enableToBottom(child);
    }
}

void Config::disable(QUuid const &id)
{
    if (!_nodes.contains(id))
    {
        qWarning() << "Failed to disable node" << id << "due to one doesn't exist.";
        return;
    }

    if (_nodes[id].disabled())
    {
        qWarning() << "Failed to disable node" << id << "due to one is disabled already.";
        return;
    }

    disableFromBottom(id);
    emit disableFinished(id);
}

void Config::rename(QUuid const &id, QString const &name)
{
    if (!_nodes.contains(id))
    {
        qWarning() << "Failed to rename node" << id << "due to one doesn't exist.";
        return;
    }

    auto &node = _nodes[id];
    if (node.name() == name)
    {
        qWarning() << "Failed to rename node" << id << "due to one has actual name.";
        return;
    }

    node.setName(name);
    emit renamed(id);
}

void Config::update(QUuid const &id, QVariantHash const &params)
{
    if (!_nodes.contains(id))
    {
        qWarning() << "Failed to update node" << id << "due to one doesn't exist.";
        return;
    }

    auto &node = _nodes[id];
    node.setParams(params);

    emit updated(id);
}

void Config::setProcessState(QUuid const &id, QProcess::ProcessState state)
{
    if (!_nodes.contains(id))
    {
        qWarning() << "Failed to update node" << id << "due to one doesn't exist.";
        return;
    }

    auto &node = _nodes[id];
    node.setProcessState(state);
    emit processStateChanged(id);
}

void Config::setRuntimeParam(QUuid const &id, QString const &key, QVariant const &param)
{
    if (!_nodes.contains(id))
    {
        qWarning() << "Failed to set runtime param for node" << id << "due to one doesn't exist.";
        return;
    }
    auto &node = _nodes[id];
    node.setRuntimeParam(key, param);
    emit runtimeParamChanged(id, key);
}

void Config::disableFromBottom(QUuid const &id)
{
    for(auto const &child : _children[id])
        disableFromBottom(child);

    auto &node = _nodes[id];
    if (node.enabled())
    {
        node.disable();
        emit disabled(id);
    }
}
