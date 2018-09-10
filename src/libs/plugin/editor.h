#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QUuid>
#include <editor_data.h>
#include <slave_as_params.h>
#include "plugin_global.h"

class Config;
class Plugins;
class Corebus;

class PLUGIN_SHARED_EXPORT Editor : public QWidget
{
    Q_OBJECT

public:
    explicit Editor(EditorData const &data, QWidget &parent);

public:
    virtual SlaveAsParams slaveAsParams() const = 0;
    virtual void setSlaveAsParams(SlaveAsParams const &slaveAsParams) = 0;

    virtual QVariantHash params() const = 0;
    virtual void setParams(QVariantHash const &params) = 0;

    virtual QStringList errors() const = 0;

protected:
    QUuid const _id;
    Config const &_config;
    Plugins const &_plugins;
    Corebus &_corebus;
};

#endif // EDITOR_H
