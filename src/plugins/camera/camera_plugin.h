#ifndef CAMERA_PLUGIN_H
#define CAMERA_PLUGIN_H

#include <QCoreApplication>
#include <default_base_plugin.h>

class CameraPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.camera")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("DEVICES"); }
    QString type() const override { return QStringLiteral("CAMERA"); }
    QString defaultName() const override { return tr("Camera"); }
    QVariantHash defaultParams() const override;
    bool hasProcess() const override { return true; }
    bool hasEditor() const override { return true; }
    Editor *editor(EditorData const &data, QWidget &parent) const override;
    std::unique_ptr<NodeController> controller(Config const &config, Plugin const &plugin, Corebus &corebus) const override;
};

#endif // CAMERA_PLUGIN_H
