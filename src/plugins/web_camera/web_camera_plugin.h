#ifndef MESSAGE_VIEWER_PLUGIN_H
#define MESSAGE_VIEWER_PLUGIN_H

#include <QCoreApplication>
#include <default_base_plugin.h>

class WebCameraPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.web_camera")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("CAMERA"); }
    QString type() const override { return QStringLiteral("WEB_CAMERA"); }
    QString defaultName() const override { return tr("Web camera"); }
    bool hasProcess() const override { return true; }
    bool hasEditor() const override { return true; }
    Editor *editor(Config const &config,  Plugins const &plugins, CoreClientSocket &socket, QUuid  const &id, QWidget &parent) const override;
    std::unique_ptr<SlaveController> controller(Config const &config, Plugin const &plugin, CoreClientSocket &socket) const override;
};

#endif // MESSAGE_VIEWER_PLUGIN_H
