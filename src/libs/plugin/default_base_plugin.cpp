#include <QHash>
#include <QPainter>
#include <QSvgRenderer>
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

std::unique_ptr<SlaveController> DefaultBasePlugin::controller() const
{
    return nullptr;
}
