#ifndef SLAVE_PARAMS_VIEW_H
#define SLAVE_PARAMS_VIEW_H

#include <QStackedWidget>
#include "node_editor.h"
#include "empty_node_editor.h"

class NodeParamsView : public QWidget
{
    Q_OBJECT

public:
    explicit NodeParamsView(Config &config, Plugins &plugins, Corebus &corebus, QWidget &parent);
    
public:
    void select(QUuid const &id);

private:
    bool hasEditor(QUuid const &id) const;

private:
    Config &_config;
    Plugins &_plugins;
    QStackedWidget _stackedWidget;
    NodeEditor _nodeEditor;
    EmptyNodeEditor _emptyNodeEditor;
};

#endif // SLAVE_PARAMS_VIEW_H
