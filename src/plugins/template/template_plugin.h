#ifndef TEMPLATE_PLUGIN_H
#define TEMPLATE_PLUGIN_H

#include <default_base_plugin.h>

class TeamplatePlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.template")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("ROOT"); }
    QString type() const override { return QStringLiteral("TEMPLATE"); }
    QString defaultName() const override { return tr("Template"); }
    bool hasProcess() const override { return true; }
    bool hasEditor() const override { return true; }
    Editor *editor(EditorData const &data, QWidget &parent) const override;
    std::unique_ptr<SlaveController> controller(Config const &config, Plugin const &plugin, Corebus &corebus) const override;
};

#endif // TEMPLATE_PLUGIN_H
