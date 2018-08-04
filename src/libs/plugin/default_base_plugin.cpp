#include <QHash>
#include <QPainter>
#include <QSvgRenderer>
#include "default_base_plugin.h"

inline uint qHash(QSize const &key)
{
    return qHash(key.width()) ^ static_cast<uint>(key.height());
}

QPixmap DefaultBasePlugin::pixmap(QSize const &size) const
{
    static QHash<QString, QHash<QSize, QPixmap>> pixmaps;

    if (!pixmaps.contains(type()))
    {
        if (!pixmaps[type()].contains(size))
        {
            QPixmap pixmap{ size };
            pixmap.fill(QColor{ 0, 0, 0, 0 });
            QPainter painter{ &pixmap };
            QSvgRenderer{ QStringLiteral(":/%1.svg").arg(type().toLower()) }.render(&painter);
            pixmaps[type()][size] = std::move(pixmap);
        }
    }

    return pixmaps[type()][size];
}

QString DefaultBasePlugin::process() const
{
    return hasProcess() ? type().toLower() : QString{};
}

Editor *DefaultBasePlugin::editor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent) const
{
    Q_UNUSED(config)
    Q_UNUSED(plugins)
    Q_UNUSED(socket)
    Q_UNUSED(id)
    Q_UNUSED(parent)
    return nullptr;
}

std::unique_ptr<SlaveController> DefaultBasePlugin::controller(Config const &config, Plugin const &plugin, CoreClientSocket &socket) const
{
    Q_UNUSED(config)
    Q_UNUSED(plugin)
    Q_UNUSED(socket)
    return nullptr;
}
