#ifndef RESPONDENT_PLACE_PLUGIN_H
#define RESPONDENT_PLACE_PLUGIN_H

#include <default_base_plugin.h>

class RespondentPlacePlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.respondent_place")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("RESPONDENT_PLACES"); }
    QString type() const override { return QStringLiteral("RESPONDENT_PLACE"); }
    QString defaultName() const override { return tr("Respondent place"); }
    bool hasEditor() const override { return true; }
    Editor *editor(EditorData const &data, QWidget &parent) const override;
    QStringList watchedSlaveKeys() const override { return { QStringLiteral("devices"), }; }
};

#endif // RESPONDENT_PLACE_PLUGIN_H
