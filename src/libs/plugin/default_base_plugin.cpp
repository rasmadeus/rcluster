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
    return hasProcess() ? type().toLower() : QString{};
}

Editor *DefaultBasePlugin::editor(EditorData const &data, QWidget &parent) const
{
    Q_UNUSED(data)
    Q_UNUSED(parent)
    return nullptr;
}

std::unique_ptr<SlaveController> DefaultBasePlugin::controller(Config const &config, Plugin const &plugin, Corebus &corebus) const
{
    Q_UNUSED(config)
    Q_UNUSED(plugin)
    Q_UNUSED(corebus)
    return nullptr;
}

QStringList DefaultBasePlugin::watchedSlaveKeys() const
{
    return {};
}

void DefaultBasePlugin::onWatchedSlaveRemoved(Config &config, QUuid const &watchedSlave, QUuid const &thisTypeSlave) const
{
    auto const slave = config.slave(thisTypeSlave);
    Q_ASSERT(slave.type() == type());
    auto params = slave.params();
    bool paramsChanged = false;

    for(auto const &key : watchedSlaveKeys())
    {
        {
            auto slaveId = params.value(key).toUuid();
            if (slaveId == watchedSlave)
            {
                params[key] = QUuid{};
                paramsChanged = true;
                continue;
            }
        }
        {
            auto slaveIds = params.value(key).toList();
            auto it = std::remove_if(slaveIds.begin(), slaveIds.end(), [&watchedSlave](auto const &id){
                return watchedSlave == id.toUuid();
            });
            if (it != slaveIds.end())
            {
                slaveIds.erase(it, slaveIds.end());
                params[key] = slaveIds;
                paramsChanged = true;
            }
        }
    }

    if (paramsChanged)
        config.update(thisTypeSlave, params);
}

bool DefaultBasePlugin::isSlaveWatched(Config &config, QUuid const &watchedSlave, QUuid const &thisTypeSlave) const
{
    auto const slave = config.slave(thisTypeSlave);
    Q_ASSERT(slave.type() == type());
    auto params = slave.params();

    for(auto const &key : watchedSlaveKeys())
    {
        {
            auto slaveId = params.value(key).toUuid();
            if (slaveId == watchedSlave)
                return true;
        }
        {
            auto slaveIds = params.value(key).toList();
            auto it = std::remove_if(slaveIds.begin(), slaveIds.end(), [&watchedSlave](auto const &id){
                return watchedSlave == id.toUuid();
            });
            if (it != slaveIds.end())
                return true;
        }
    }
    return false;
}

bool DefaultBasePlugin::isListener(Config &config, QUuid const &messageSource, QUuid const &thisTypeSlave) const
{
    Q_UNUSED(config)
    Q_UNUSED(messageSource)
    Q_UNUSED(thisTypeSlave)
    return false;
}
