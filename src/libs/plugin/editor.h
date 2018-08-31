#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QUuid>
#include <slave_as_params.h>
#include "plugin_global.h"

class Config;
class Corebus;
class Plugins;

class PLUGIN_SHARED_EXPORT Editor : public QWidget
{
    Q_OBJECT

public:
    explicit Editor(QWidget &parent);

public:
    virtual void init() = 0;

    virtual SlaveAsParams slaveAsParams() const = 0;
    virtual void setSlaveAsParams(SlaveAsParams const &slaveAsParams) = 0;

    virtual QVariantHash params() const = 0;
    virtual void setParams(QVariantHash const &params) = 0;

    virtual QStringList errors() const = 0;

public:
    void setConfig(Config const &config) { _config = &config; }
    void setPlugins(Plugins const &plugins) { _plugins = &plugins; }
    void setCorebus(Corebus &corebus) { _corebus = &corebus; }
    void setId(QUuid const &id) { _id = id; }

protected:
    Config const *_config{ nullptr };
    Plugins const *_plugins{ nullptr };
    Corebus *_corebus{ nullptr };
    QUuid _id;
};

#endif // EDITOR_H
