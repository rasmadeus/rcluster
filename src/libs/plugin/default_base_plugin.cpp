#include <QHash>
#include <QPainter>
#include <QSvgRenderer>
#include <config.h>
#include <svg.h>
#include "default_base_plugin.h"

inline uint qHash(QSize const &key)
{
    return qHash(key.width()) ^ static_cast<uint>(key.height());
}

QPixmap DefaultBasePlugin::pixmap(QSize const &size) const
{
    static QHash<QString, QHash<QSize, QPixmap>> pixmaps;

    if (!pixmaps.contains(type()) && !pixmaps[type()].contains(size))
        pixmaps[type()][size] = rcluster::fromSvg(type().toLower(), size);

    return pixmaps[type()][size];
}

QString DefaultBasePlugin::process() const
{
    return hasProcess() ?type().toLower() : QString{};
}

Editor *DefaultBasePlugin::editor([[maybe_unused]] EditorData const &data, [[maybe_unused]] QWidget &parent) const
{
    return nullptr;
}

std::unique_ptr<NodeController> DefaultBasePlugin::controller([[maybe_unused]] Config const &config, [[maybe_unused]] Plugin const &plugin, [[maybe_unused]] Corebus &corebus) const
{
    return nullptr;
}

void DefaultBasePlugin::onNodeRemoved([[maybe_unused]] Config &config, [[maybe_unused]] QUuid const &watchedNode, [[maybe_unused]] QUuid const &thisTypeNode) const
{
}

void DefaultBasePlugin::onNodeUpdated([[maybe_unused]] Config &config, [[maybe_unused]] QUuid const &updatedNode, [[maybe_unused]] QUuid const &thisTypeNode) const
{
}

bool DefaultBasePlugin::isListener([[maybe_unused]] Config &config, [[maybe_unused]] QString const &messageSource, [[maybe_unused]] QUuid const &thisTypeNode) const
{
    return false;
}

void DefaultBasePlugin::clearParamList(Config &config, QUuid const &removedNode, QUuid const &thisTypeNode, QString const &paramKey) const
{
    auto params = config.node(thisTypeNode).params();
    auto param = params.value(paramKey).toList();
    auto it = std::remove_if(param.begin(), param.end(), [&removedNode](auto const &id){ return id.toUuid() == removedNode;  });
    if (it != param.end())
    {
        param.erase(it, param.end());
        params[paramKey] = std::move(param);
        config.update(thisTypeNode, params);
    }
}

void DefaultBasePlugin::clearParam(Config &config, QUuid const &removedNode, QUuid const &thisTypeNode, QString const &paramKey) const
{
    auto params = config.node(thisTypeNode).params();
    auto param = params.value(paramKey).toUuid();
    if (param == removedNode)
    {
        params[paramKey] = QUuid{};
        config.update(thisTypeNode, params);
    }
}

void DefaultBasePlugin::updateParamList(Config &config, QUuid const &updatedNode, QUuid const &thisTypeNode, QString const &paramKey) const
{
    auto params = config.node(thisTypeNode).params();
    auto param = params.value(paramKey).toList();
    if (std::any_of(param.cbegin(), param.cend(), [&updatedNode](auto const &id) { return id.toUuid() == updatedNode; }))
        config.update(thisTypeNode, params);
}

void DefaultBasePlugin::updateParam(Config &config, QUuid const &updatedNode, QUuid const &thisTypeNode, QString const &paramKey) const
{
    auto params = config.node(thisTypeNode).params();
    auto param = params.value(paramKey).toUuid();
    if (param == updatedNode)
        config.update(thisTypeNode, params);
}

bool DefaultBasePlugin::isListenerParamList(Config &config, QString const &messageSource, QUuid const &thisTypeNode, QString const &paramKey) const
{
    auto params = config.node(thisTypeNode).params();
    auto param = params.value(paramKey).toList();
    return std::any_of(param.cbegin(), param.cend(), [&messageSource](auto const &id) { return id.toUuid() == QUuid::fromString(messageSource); });
}

bool DefaultBasePlugin::isListenerParam(Config &config, QString const &messageSource, QUuid const &thisTypeNode, QString const &paramKey) const
{
    auto params = config.node(thisTypeNode).params();
    auto param = params.value(paramKey).toUuid();
    return param == QUuid::fromString(messageSource);
}
