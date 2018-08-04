#include <QHBoxLayout>
#include <QUuid>
#include <globals.h>
#include <config.h>
#include <plugins.h>
#include "slave_params_view.h"

SlaveParamsView::SlaveParamsView(Config &config, Plugins &plugins, CoreClientSocket &socket, QWidget &parent)
    : QWidget{ &parent }
    , _config{ config }
    , _plugins{ plugins }
    , _stackedWidget{ this }
    , _slaveEditor{ config, plugins, socket, *this }
    , _emptySlaveEditor{ *this }
{
    _stackedWidget.addWidget(&_slaveEditor);
    _stackedWidget.addWidget(&_emptySlaveEditor);

    _stackedWidget.layout()->setMargin(0);
    _stackedWidget.layout()->setSpacing(rcluster::layoutGap());

    auto mainLayout = new QHBoxLayout{ this };
    mainLayout->setMargin(rcluster::layoutGap());
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_stackedWidget);

    _stackedWidget.setCurrentWidget(&_emptySlaveEditor);
}

void SlaveParamsView::select(QUuid const &id)
{
    if (hasEditor(id))
    {
        _slaveEditor.select(id);
        _stackedWidget.setCurrentWidget(&_slaveEditor);
    }
    else
    {
        _slaveEditor.clear();
        _stackedWidget.setCurrentWidget(&_emptySlaveEditor);
    }
}

bool SlaveParamsView::hasEditor(QUuid const &id) const
{
    if (id.isNull())
        return false;

    Q_ASSERT(_config.hasSlave(id));
    return _plugins.plugin(_config.slave(id).type())->hasEditor();
}
