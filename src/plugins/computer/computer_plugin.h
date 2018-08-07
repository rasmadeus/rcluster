#ifndef COMPUTER_PLUGIN_H
#define COMPUTER_PLUGIN_H

#include <QCoreApplication>
#include <default_base_plugin.h>

class ComputerPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.computer")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("ROOT"); }
    QString type() const override { return QStringLiteral("COMPUTER"); }
    QString defaultName() const override { return tr("Computer"); }
    QVariantHash defaultParams() const override;
    bool hasProcess() const override { return true; }
    bool hasEditor() const override { return true; }
    Editor *editor(QWidget &parent) const override;
    std::unique_ptr<SlaveController> controller() const override;
};

#endif // COMPUTER_PLUGIN_H
