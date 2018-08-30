#ifndef PLUGINS_H
#define PLUGINS_H

#include "plugin.h"

class PLUGIN_SHARED_EXPORT Plugins
{
public:
    static Plugin *load(QString const &type);

public:
    ~Plugins() { clear(); }

public:
    void load();
    std::vector<Plugin*> children(QString const &type) const;
    Plugin* plugin(QString const &type) const { return _plugins[type]; }
    bool contains(QString const &type) const { return _plugins.contains(type); }

private:
    void clear();

private:
    QHash<QString, Plugin*> _plugins;
};

#endif // PLUGINS_H
