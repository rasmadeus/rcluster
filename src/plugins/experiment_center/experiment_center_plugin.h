#ifndef EXPERIMENT_CENTER_PLUGIN_H
#define EXPERIMENT_CENTER_PLUGIN_H

#include <QCoreApplication>
#include <default_base_plugin.h>

class ExperimentCenterPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.experiment_center")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("DISPLAY"); }
    QString type() const override { return QStringLiteral("EXPERIMENT_CENTER"); }
    QString defaultName() const override { return tr("Experiment center"); }
    bool hasProcess() const override { return true; }
    bool hasEditor() const override { return true; }
    Editor *editor(EditorData const &data, QWidget &parent) const override;
    std::unique_ptr<SlaveController> controller(Config const &config, Plugin const &plugin, Corebus &corebus) const override;
    QStringList watchedSlaveKeys() const override { return { QStringLiteral("respondent_places"), }; }
};

#endif // EXPERIMENT_CENTER_PLUGIN_H
