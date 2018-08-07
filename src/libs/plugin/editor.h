#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QUuid>
#include "plugin_global.h"

class Config;
class CoreClientSocket;
class Plugins;

class PLUGIN_SHARED_EXPORT Editor : public QWidget
{
    Q_OBJECT

public:
    explicit Editor(QWidget &parent);

public:
    virtual void init() = 0;

    virtual QSet<QUuid> events() const = 0;
    virtual void setEvents(QSet<QUuid> const &events) = 0;

    virtual QVariantHash params() const = 0;
    virtual void setParams(QVariantHash const &params) = 0;

    virtual QStringList errors() const = 0;

public:
    void setConfig(Config const &config) { _config = &config; }
    void setPlugins(Plugins const &plugins) { _plugins = &plugins; }
    void setSocket(CoreClientSocket &socket) { _socket = &socket; }
    void setId(QUuid const &id) { _id = id; }

protected:
    Config const *_config{ nullptr };
    Plugins const *_plugins{ nullptr };
    CoreClientSocket *_socket{ nullptr };
    QUuid _id;
};

#endif // EDITOR_H
