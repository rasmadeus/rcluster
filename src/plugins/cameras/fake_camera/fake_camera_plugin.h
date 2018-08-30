#ifndef FAKE_CAMERA_PLUGIN_H
#define FAKE_CAMERA_PLUGIN_H

#include <QCoreApplication>
#include <default_base_plugin.h>

class FakeCameraPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.fake_camera")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("CAMERAS"); }
    QString type() const override { return QStringLiteral("FAKE_CAMERA"); }
    QString defaultName() const override { return tr("Fake camera"); }
    bool hasProcess() const override { return true; }
    std::unique_ptr<SlaveController> controller() const override;
};

#endif // FAKE_CAMERA_PLUGIN_H
