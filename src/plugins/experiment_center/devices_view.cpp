#include <QHeaderView>
#include <QVBoxLayout>
#include <globals.h>
#include "devices_view.h"

DevicesView::DevicesView(Config const &config, Plugins const &plugins, QWidget *parent)
    : QWidget{ parent }
    , _config{ config }
    , _model{ config, plugins }
{
    _view.setSelectionMode(QAbstractItemView::SingleSelection);
    _view.setSelectionBehavior(QAbstractItemView::SelectRows);
    _view.setModel(&_model);
    _view.horizontalHeader()->setStretchLastSection(true);
    _view.verticalHeader()->hide();

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(rcluster::layoutGap());
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_view);
}

void DevicesView::onSetup(Slave const &slave)
{
    _model.onSetup(slave);
}
