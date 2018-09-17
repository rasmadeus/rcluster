#include <QHeaderView>
#include <QVBoxLayout>
#include <globals.h>
#include <config.h>
#include <slave.h>
#include "device_view.h"

DeviceView::DeviceView(Config const &config, Plugins const &plugins, QWidget *parent)
    : QWidget{ parent }
    , _config{ config }
    , _model{ config, plugins, *this }
    , _proxyModel{ *this }
{
    _proxyModel.setSourceModel(&_model);

    _view.setModel(&_proxyModel);
    _view.header()->setSectionResizeMode(DeviceModel::ColumnCaption, QHeaderView::ResizeToContents);
    _view.header()->setSectionResizeMode(DeviceModel::ColumnInfo, QHeaderView::Stretch);
    _view.header()->setSectionResizeMode(DeviceModel::ColumnState, QHeaderView::ResizeToContents);
    //_view.header()->hide();

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->setMargin(0);
    mainLayout->addWidget(&_view);
}

void DeviceView::onSetup(Slave const &slave)
{
    _model.onSetup(slave);
    _proxyModel.sort(DeviceModel::ColumnCaption);
    _view.expandAll();
}
