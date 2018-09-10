#ifndef WEB_CAMERA_PLUGIN_H
#define WEB_CAMERA_PLUGIN_H

#include <QCoreApplication>
#include <default_base_plugin.h>

class WebCameraPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.web_camera")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("CAMERAS"); }
    QString type() const override { return QStringLiteral("WEB_CAMERA"); }
    QString defaultName() const override { return tr("Web camera"); }
    bool hasProcess() const override { return true; }
    bool hasEditor() const override { return true; }
    Editor *editor(QWidget &parent) const override;
    std::unique_ptr<SlaveController> controller() const override;
};

#endif // WEB_CAMERA_PLUGIN_H
