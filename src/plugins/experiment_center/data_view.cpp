#include <QVBoxLayout>
#include <QUuid>
#include <globals.h>
#include "data_view.h"
#include "devices_data_view.h"

DataView::DataView(Config const &config, Plugins const &plugins, QWidget &parent)
    : QWidget{ &parent }
    , _config{ config }
    , _plugins{ plugins }
{
    _tabs.setTabsClosable(true);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_tabs);

    connect(&_tabs, &QTabWidget::tabCloseRequested, this, &DataView::removeTab);
}

void DataView::onSetup(Slave const &slave)
{
    for(int i = 0; i < _tabs.count(); ++i)
        static_cast<DevicesDataView*>(_tabs.widget(i))->onSetup(slave);
}

void DataView::appendTab()
{
    _tabs.addTab(new DevicesDataView{ _config, _plugins, _tabs }, makeTabText(_tabs.count()));
}

void DataView::appendDeviceView(QUuid const &id, QString const &type)
{
    Q_ASSERT(!id.isNull());

    if (_tabs.count() == 0)
        appendTab();

    auto currentWidget = _tabs.currentWidget();
    Q_ASSERT(currentWidget != nullptr);
    static_cast<DevicesDataView*>(currentWidget)->appendView(id, type);
}

void DataView::arrangeTile()
{
    if (_tabs.count() > 0)
        static_cast<DevicesDataView*>(_tabs.currentWidget())->tileSubWindows();
}

void DataView::arrangeCascade()
{
    if (_tabs.count() > 0)
        static_cast<DevicesDataView*>(_tabs.currentWidget())->cascadeSubWindows();
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
