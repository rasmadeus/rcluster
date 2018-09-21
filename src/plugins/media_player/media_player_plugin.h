#ifndef MEDIA_PLAYER_PLUGIN_H
#define MEDIA_PLAYER_PLUGIN_H

#include <default_base_plugin.h>

class MediaPlayerPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.media_player")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("COMPUTER"); }
    QString type() const override { return QStringLiteral("MEDIA_PLAYER"); }
    QString defaultName() const override { return tr("Media Player"); }
    bool hasProcess() const override { return true; }
    bool hasEditor() const override { return true; }
    Editor *editor(EditorData const &data, QWidget &parent) const override;
    std::unique_ptr<SlaveController> controller(Config const &config, Plugin const &plugin, Corebus &corebus) const override;
};

#endif // MEDIA_PLAYER_PLUGIN_H
