#include <unordered_map>
#include <QDebug>
#include "config.h"
#include <plugins.h>
#include "slave_model.h"

SlaveModel::SlaveModel(Config const &config, Plugins const &plugins, QObject &parent)
    : SlaveItemModel{ config, plugins, &parent }
{
    reloadSlaves();

    connect(&_config, &Config::reseted, this, &SlaveModel::reloadSlaves);
    connect(&_config, &Config::appended, this, &SlaveModel::appendSlaveById);
    connect(&_config, &Config::removeFinished, this, &SlaveModel::removeSlave);
    connect(&_config, &Config::renamed, this, &SlaveModel::updateSlave);
    connect(&_config, &Config::renamed, this, &SlaveModel::renamed);
    connect(&_config, &Config::enabled, this, &SlaveModel::updateSlave);
    connect(&_config, &Config::disabled, this, &SlaveModel::updateSlave);
    connect(&_config, &Config::updated, this, &SlaveModel::updateSlave);
    connect(&_config, &Config::processStateChanged, this, &SlaveModel::updateSlave);
    connect(&_config, &Config::runtimeParamChanged, this, &SlaveModel::updateSlave);
}

QVariant SlaveModel::data(QModelIndex const &index, int role) const
{
    if (!index.isValid())
        return {};

    switch(role)
    {
        case Qt::BackgroundRole: return dataBackground(index);
        default: return SlaveItemModel::data(index, role);
    }
}

void SlaveModel::appendSlaveById(QUuid const &id)
{
    appendSlave(id);
}

void SlaveModel::appendChildren(QUuid const &id, SlaveItem &item)
{
    for(auto const &child : _config.children(id))
    {
        item.append(child);
        appendChildren(child, item.lastChild());
    }
}

void SlaveModel::reloadSlaves()
{
    beginResetModel();
    _root.clear();
    appendChildren({}, _root);
    endResetModel();
    emit reloaded();
}

QVariant SlaveModel::dataBackground(QModelIndex const &index) const
{
    auto const slave = this->slave(index);
    if (!_plugins.plugin(slave.type())->hasProcess() || slave.disabled())
        return {};

    return slave.processState() == QProcess::ProcessState::Running ? QVariant{} : QColor{ 255, 150, 150 };
}
