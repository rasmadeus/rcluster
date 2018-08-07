#ifndef NTP_CLIENT_PLUGIN_H
#define NTP_CLIENT_PLUGIN_H

#include <QCoreApplication>
#include <default_base_plugin.h>

class NtpClientPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.ntp_client")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("COMPUTER"); }
    QString type() const override { return QStringLiteral("NTP_CLIENT"); }
    QString defaultName() const override { return tr("NTP client"); }
    QVariantHash defaultParams() const override;
    bool hasProcess() const override { return true; }
    bool hasEditor() const override { return true; }
    Editor *editor(QWidget &parent) const override;
    std::unique_ptr<SlaveController> controller() const override;
};

#endif // NTP_CLIENT_PLUGIN_H
