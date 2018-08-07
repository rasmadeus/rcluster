#ifndef MESSAGE_VIEWER_PLUGIN_H
#define MESSAGE_VIEWER_PLUGIN_H

#include <QCoreApplication>
#include <default_base_plugin.h>

class MessageViewerPlugin : public QObject, public DefaultBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rcluster.plugin.message_viewer")
    Q_INTERFACES(Plugin)

public:
    QString parent() const override { return QStringLiteral("DISPLAY"); }
    QString type() const override { return QStringLiteral("MESSAGE_VIEWER"); }
    QString defaultName() const override { return tr("Message Viewer"); }
    bool hasProcess() const override { return true; }
    bool hasEditor() const override { return true; }
    Editor *editor(QWidget &parent) const override;
    std::unique_ptr<SlaveController> controller() const override;
};

#endif // MESSAGE_VIEWER_PLUGIN_H
