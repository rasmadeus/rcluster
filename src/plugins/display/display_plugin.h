#ifndef DISPLAY_PLUGIN_H
#define DISPLAY_PLUGIN_H

#include <QCoreApplication>
#include <default_base_plugin.h>

class DisplayPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.display")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("COMPUTER"); }
    QString type() const override { return QStringLiteral("DISPLAY"); }
    QString defaultName() const override { return tr("Display"); }
};

#endif // DISPLAY_PLUGIN_H
