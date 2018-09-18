#include <QVBoxLayout>
#include <QUuid>
#include <globals.h>
#include "data_view.h"
#include "device_data_view.h"

DataView::DataView(Config const &config, QWidget &parent)
    : QWidget{ &parent }
    , _config{ config }
{
    _tabs.setTabsClosable(true);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_tabs);

    connect(&_tabs, &QTabWidget::tabCloseRequested, this, &DataView::removeTab);
}

void DataView::appendTab()
{
    _tabs.addTab(new DeviceDataView{ _config, _tabs }, makeTabText(_tabs.count()));
}

void DataView::appendDeviceView(QUuid const &id, QString const &type)
{
    Q_ASSERT(!id.isNull());

    if (_tabs.count() == 0)
        appendTab();

    auto currentWidget = _tabs.currentWidget();
    Q_ASSERT(currentWidget != nullptr);
    static_cast<DeviceDataView*>(currentWidget)->appendView(id, type);
}

void DataView::removeTab(int index)
{
    _tabs.widget(index)->deleteLater();
    _tabs.removeTab(index);
    updateTabTitles();
}

void DataView::updateTabTitles()
{
    for(int i = 0; i < _tabs.count(); ++i)
        _tabs.setTabText(i, makeTabText(i));
}
