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
    QString parent() const override { return QStringLiteral("COMPUTER"); }
    QString type() const override { return QStringLiteral("CAMERA"); }
    QString defaultName() const override { return tr("Cameras"); }
    bool hasProcess() const override { return false; }
};

#endif //CAMERA_PLUGIN
