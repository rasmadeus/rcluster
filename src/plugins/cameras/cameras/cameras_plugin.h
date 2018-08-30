#ifndef CAMERAS_PLUGIN_H
#define CAMERAS_PLUGIN_H

#include <QCoreApplication>
#include <default_base_plugin.h>

class CamerasPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.camera")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("COMPUTER"); }
    QString type() const override { return QStringLiteral("CAMERAS"); }
    QString defaultName() const override { return tr("Cameras"); }
    bool hasProcess() const override { return false; }
};

#endif //CAMERAS_PLUGIN
