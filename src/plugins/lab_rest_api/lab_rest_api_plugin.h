#ifndef LAB_REST_API_PLUGIN_H
#define LAB_REST_API_PLUGIN_H

#include <default_base_plugin.h>

class LabRestApiPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.lab_rest_api")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("COMPUTER"); }
    QString type() const override { return QStringLiteral("LAB_REST_API"); }
    QString defaultName() const override { return tr("Labaratory Rest API"); }
    bool hasProcess() const override { return true; }
    bool hasEditor() const override { return true; }
    Editor *editor(EditorData const &data, QWidget &parent) const override;
    std::unique_ptr<SlaveController> controller(Config const &config, Plugin const &plugin, Corebus &corebus) const override;
};

#endif // LAB_REST_API_PLUGIN_H
