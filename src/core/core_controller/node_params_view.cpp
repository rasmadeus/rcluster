#include <QHBoxLayout>
#include <QUuid>
#include <globals.h>
#include <config.h>
#include <plugins.h>
#include "node_params_view.h"

NodeParamsView::NodeParamsView(Config &config, Plugins &plugins, Corebus &corebus, QWidget &parent)
    : QWidget{ &parent }
    , _config{ config }
    , _plugins{ plugins }
    , _stackedWidget{ this }
    , _nodeEditor{ config, plugins, corebus, *this }
    , _emptyNodeEditor{ *this }
{
    _stackedWidget.addWidget(&_nodeEditor);
    _stackedWidget.addWidget(&_emptyNodeEditor);

    _stackedWidget.layout()->setMargin(0);
    _stackedWidget.layout()->setSpacing(rcluster::layoutGap());

    auto mainLayout = new QHBoxLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_stackedWidget);

    _stackedWidget.setCurrentWidget(&_emptyNodeEditor);
}

void NodeParamsView::select(QUuid const &id)
{
    if (hasEditor(id))
    {
        _nodeEditor.select(id);
        _stackedWidget.setCurrentWidget(&_nodeEditor);
    }
    else
    {
        _nodeEditor.clear();
        _stackedWidget.setCurrentWidget(&_emptyNodeEditor);
    }
}

bool NodeParamsView::hasEditor(QUuid const &id) const
{
    if (id.isNull())
        return false;

    Q_ASSERT(_config.hasNode(id));
    return _plugins.plugin(_config.node(id).type())->hasEditor();
}
