#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include "plugins.h"

Plugin* Plugins::load(QString const &type)
{
    QDir pluginsDir{ qApp->applicationDirPath() };
    if (!pluginsDir.cd(QStringLiteral("plugins")))
    {
        qCritical() << "Failed to find plugin's dir";
        return {};
    }

    QPluginLoader pluginLoader{ pluginsDir.absoluteFilePath(type) };
    auto plugin = pluginLoader.instance();
    if (!plugin)
    {
        qCritical() << QStringLiteral("Failed to load the plugin %1.").arg(type);
        return {};
    }

    return qobject_cast<Plugin*>(plugin);
}

void Plugins::load()
{
    clear();

    QDir pluginsDir{ qApp->applicationDirPath() };
    if (!pluginsDir.cd(QStringLiteral("plugins")))
    {
        qCritical() << "Failed to find plugin's dir";
        return;
    }

    for (QString const &fileName : pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader pluginLoader{ pluginsDir.absoluteFilePath(fileName) };
        auto instance = pluginLoader.instance();
        if (!instance)
        {
            qCritical() << QStringLiteral("Failed to load the plugin %1.").arg(fileName);
            continue;
        }

        auto plugin = qobject_cast<Plugin*>(instance);
        Q_ASSERT(plugin);

        if (_plugins.contains(plugin->type()))
        {
            qWarning() << "Plugin " << plugin->type() << " has been already loaded. Failed to load another.";
            continue;
        }

        _plugins[plugin->type()] = plugin;
    }
}

std::vector<Plugin *> Plugins::children(QString const &type) const
{
    std::vector<Plugin*> res;
    for(auto const &plugin : _plugins)
        if (plugin->parent() == type)
            res.push_back(plugin);
    return res;
}

void Plugins::clear()
{
    qDeleteAll(_plugins);
    _plugins.clear();
}
