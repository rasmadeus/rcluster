#include <unordered_map>
#include <QDebug>
#include "config.h"
#include <plugins.h>
#include "node_model.h"

NodeModel::NodeModel(Config const &config, Plugins const &plugins, QObject &parent)
    : NodeItemModel{ config, plugins, &parent }
{
    reloadNodes();

    connect(&_config, &Config::reseted, this, &NodeModel::reloadNodes);
    connect(&_config, &Config::appended, this, &NodeModel::appendNodeById);
    connect(&_config, &Config::removeFinished, this, &NodeModel::removeNode);
    connect(&_config, &Config::renamed, this, &NodeModel::updateNode);
    connect(&_config, &Config::renamed, this, &NodeModel::renamed);
    connect(&_config, &Config::enabled, this, &NodeModel::updateNode);
    connect(&_config, &Config::disabled, this, &NodeModel::updateNode);
    connect(&_config, &Config::updated, this, &NodeModel::updateNode);
    connect(&_config, &Config::processStateChanged, this, &NodeModel::updateNode);
    connect(&_config, &Config::runtimeParamChanged, this, &NodeModel::updateNode);
}

QVariant NodeModel::data(QModelIndex const &index, int role) const
{
    if (!index.isValid())
        return {};

    switch(role)
    {
        case Qt::BackgroundRole: return dataBackground(index);
        case Qt::TextColorRole: return dataTextColor(index);
        default: return NodeItemModel::data(index, role);
    }
}

void NodeModel::appendNodeById(QUuid const &id)
{
    appendNode(id);
}

void NodeModel::appendChildren(QUuid const &id, NodeItem &item)
{
    for(auto const &child : _config.children(id))
    {
        item.append(child);
        appendChildren(child, item.lastChild());
    }
}

void NodeModel::reloadNodes()
{
    beginResetModel();
    _root.clear();
    appendChildren({}, _root);
    endResetModel();
    emit reloaded();
}

QVariant NodeModel::dataBackground(QModelIndex const &index) const
{
    auto const node = this->node(index);
    if (!_plugins.plugin(node.type())->hasProcess() || node.disabled())
        return {};

    if (node.processState() != QProcess::ProcessState::Running)
        return QColor{ 255, 210, 210 };

    return {};
}

QVariant NodeModel::dataTextColor(QModelIndex const &index) const
{
    auto const node = this->node(index);
    if (node.isFake())
        return QColor{ 200, 0, 0 };

    return {};
}
