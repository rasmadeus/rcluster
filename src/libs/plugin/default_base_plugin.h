#ifndef DEFAULT_BASE_PLUGIN_H
#define DEFAULT_BASE_PLUGIN_H

#include <QVariantHash>
#include "plugin.h"
#include "node_controller.h"

class PLUGIN_SHARED_EXPORT DefaultBasePlugin : public Plugin
{
public:
    QPixmap pixmap(QSize const &size = QSize{ 16, 16 }) const override;
    QVariantHash defaultParams() const override { return {}; }
    QString process() const override;
    bool hasEditor() const override { return false; }
    bool hasProcess() const override { return false; }
    Editor *editor(EditorData const &data, QWidget &parent) const override;
    std::unique_ptr<NodeController> controller(Config const &config, Plugin const &plugin, Corebus &corebus) const override;
    void onNodeRemoved(Config &config, QUuid const &removedNode, QUuid const &thisTypeNode) const override;
    void onNodeUpdated(Config &config, QUuid const &updatedNode, QUuid const &thisTypeNode) const override;
    bool isListener(Config &config, QString const &messageSource, QUuid const &thisTypeNode) const override;

protected:
    void clearParamList(Config &config, QUuid const &removedNode, QUuid const &thisTypeNode, QString const &paramKey) const;
    void clearParam(Config &config, QUuid const &removedNode, QUuid const &thisTypeNode, QString const &paramKey) const;
    void updateParamList(Config &config, QUuid const &updatedNode, QUuid const &thisTypeNode, QString const &paramKey) const;
    void updateParam(Config &config, QUuid const &updatedNode, QUuid const &thisTypeNode, QString const &paramKey) const;
    bool isListenerParamList(Config &config, QString const &messageSource, QUuid const &thisTypeNode, QString const &paramKey) const;
    bool isListenerParam(Config &config, QString const &messageSource, QUuid const &thisTypeNode, QString const &paramKey) const;
};

#endif // DEFAULT_BASE_PLUGIN_H
