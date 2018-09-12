#ifndef RESPONDENT_PLACES_PLUGIN_H
#define RESPONDENT_PLACES_PLUGIN_H

#include <default_base_plugin.h>

class RespondentPlacesPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.respondent_places")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("ROOT"); }
    QString type() const override { return QStringLiteral("RESPONDENT_PLACES"); }
    QString defaultName() const override { return tr("Respondent places"); }
};

#endif // RESPONDENT_PLACES_PLUGIN_H
