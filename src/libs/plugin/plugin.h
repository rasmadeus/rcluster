#ifndef PLUGIN_H
#define PLUGIN_H

#include <memory>
#include <QPixmap>
#include <QString>
#include "plugin_global.h"
#include "slave_controller.h"

class Config;
class Editor;
class Plugins;
class CoreClientSocket;

class PLUGIN_SHARED_EXPORT Plugin
{
public:
    virtual ~Plugin() = default;

public:
    virtual QString parent() const = 0;
    virtual QString type() const = 0;
    virtual QString defaultName() const = 0;
    virtual QPixmap pixmap(QSize const &size = QSize{ 16, 16 }) const = 0;
    virtual QVariantHash defaultParams() const = 0;
    virtual bool hasProcess() const = 0;
    virtual QString process() const = 0;
    virtual bool hasEditor() const = 0;
    virtual Editor* editor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent) const = 0;
    virtual std::unique_ptr<SlaveController> controller(Config const &config, Plugin const &plugin, CoreClientSocket &socket) const = 0;
};

Q_DECLARE_INTERFACE(Plugin, "rcluster.plugin")

#endif // PLUGIN_H
