#include <unordered_map>
#include <hash_functions.h>
#include <device_state.h>
#include <config.h>
#include <plugins.h>
#include <svg.h>
#include "device_record.h"

DeviceRecord::DeviceRecord(const Config &config, const Plugins &plugins)
    : _config{ config }
    , _plugins{ plugins }
{
}

QString DeviceRecord::respondentCaption() const
{
    return  _config.slave(_respondent).name();
}

QString DeviceRecord::deviceCaption() const
{
    return _config.slave(_device).name();
}

QPixmap DeviceRecord::respondentPixmap() const
{
    return _plugins.plugin(_config.slave(_respondent).type())->pixmap();
}

QPixmap DeviceRecord::devicePixmap() const
{
    return _plugins.plugin(_config.slave(_device).type())->pixmap();
}

QString DeviceRecord::deviceState() const
{
    static std::unordered_map<DeviceState, QString> const states{
        { DeviceState::Unknown, tr("Unknown") },
        { DeviceState::On, tr("On") },
        { DeviceState::Off, tr("Off") },
    };
    auto const state = _config.slave(_device).runtimeParam(QStringLiteral("state")).value<DeviceState>();
    auto const it = states.find(state);
    Q_ASSERT(it != states.cend());
    return it->second;
}

QPixmap DeviceRecord::deviceStatePixmap() const
{
    static std::unordered_map<DeviceState, QPixmap> const states{
        { DeviceState::Unknown, rcluster::fromSvg(QStringLiteral("device_off")) },
        { DeviceState::On, rcluster::fromSvg(QStringLiteral("device_on")) },
        { DeviceState::Off, rcluster::fromSvg(QStringLiteral("device_off")) },
    };
    auto const state = _config.slave(_device).runtimeParam(QStringLiteral("state")).value<DeviceState>();
    auto const it = states.find(state);
    Q_ASSERT(it != states.cend());
    return it->second;
}

QString DeviceRecord::batteryStatus() const
{
    auto const batteryParam = _config.slave(_device).runtimeParam(QStringLiteral("battery"));
    return batteryParam.isValid() ? batteryParam.toString() : tr("Unknown");
}
