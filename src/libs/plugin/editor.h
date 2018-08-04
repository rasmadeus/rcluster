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
    explicit Editor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent);

public:
    virtual QSet<QUuid> events() const = 0;
    virtual void setEvents(QSet<QUuid> const &events) = 0;

    virtual QVariantHash params() const = 0;
    virtual void setParams(QVariantHash const &params) = 0;

    virtual QStringList errors() const = 0;

public:
    void setId(QUuid const &id) { _id = id; }
    QUuid const &id() const { return _id; }

protected:
    Config const &_config;
    Plugins const &_plugins;
    CoreClientSocket &_socket;
    QUuid _id;
};

#endif // EDITOR_H
