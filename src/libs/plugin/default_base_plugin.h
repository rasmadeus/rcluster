#ifndef DEFAULT_BASE_PLUGIN_H
#define DEFAULT_BASE_PLUGIN_H

#include <QVariantHash>
#include "plugin.h"
#include "slave_controller.h"

class PLUGIN_SHARED_EXPORT DefaultBasePlugin : public Plugin
{
public:
    QPixmap pixmap(QSize const &size = QSize{ 16, 16 }) const override;
    QVariantHash defaultParams() const override { return {}; }
    QString process() const override;
    bool hasEditor() const override { return false; }
    bool hasProcess() const override { return false; }
    Editor *editor(EditorData const &data, QWidget &parent) const override;
    std::unique_ptr<SlaveController> controller(Config const &config, Plugin const &plugin, Corebus &corebus) const override;
    QStringList paramKeyContainsSlave() const override;
    void clearParams(Config &config, QUuid const &removedSlave, QUuid const &thisTypeSlave) const override;
    bool isListener(Config &config, QUuid const &messageSource, QUuid const &thisTypeSlave) const override;
};

#endif // DEFAULT_BASE_PLUGIN_H
