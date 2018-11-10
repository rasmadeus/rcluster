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
	Editor *editor(EditorData const &data, QWidget &parent) const;
	QString type() const override { return QStringLiteral("COMPUTER"); }
	QString defaultName() const override { return tr("Computer"); }
	QVariantHash defaultParams() const override;
	bool hasProcess() const override { return true; }
	bool hasEditor() const override { return true; }
	std::unique_ptr<NodeController> controller(Config const &config, Plugin const &plugin, Corebus &corebus) const override;
};

#endif // COMPUTER_PLUGIN_H
