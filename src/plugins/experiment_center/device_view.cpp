#include <QHeaderView>
#include <QVBoxLayout>
#include <QSettings>
#include <globals.h>
#include <config.h>
#include <slave.h>
#include "state_delegate.h"
#include "device_view.h"

DeviceView::DeviceView(Config const &config, Plugins const &plugins, QWidget &parent)
    : QWidget{ &parent }
    , _config{ config }
    , _model{ config, plugins, *this }
    , _proxyModel{ *this }
{
    _proxyModel.setSourceModel(&_model);
    _view.setModel(&_proxyModel);

    _view.header()->setObjectName(QStringLiteral("view_header"));
    _view.header()->setSectionsMovable(false);
    _view.header()->setStretchLastSection(false);
    _view.header()->setSectionResizeMode(DeviceModel::ColumnCaption, QHeaderView::Interactive);
    _view.header()->setSectionResizeMode(DeviceModel::ColumnRestApi, QHeaderView::Interactive);
    _view.header()->setSectionResizeMode(DeviceModel::ColumnInfo, QHeaderView::Stretch);
    _view.header()->setSectionResizeMode(DeviceModel::ColumnBattery, QHeaderView::ResizeToContents);
    _view.header()->setSectionResizeMode(DeviceModel::ColumnState, QHeaderView::ResizeToContents);

    _view.setItemDelegateForColumn(DeviceModel::ColumnState, new StateDelegate{ _config, _view });

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->setMargin(0);
    mainLayout->addWidget(&_view);

    connect(&_view, &QTreeView::doubleClicked, this, &DeviceView::onDoubleClicked);
}

void DeviceView::onSetup(Slave const &slave)
{
    _model.onSetup(slave);
    _proxyModel.sort(DeviceModel::ColumnCaption);
    _view.expandAll();
}

void DeviceView::storeSettings(QSettings &settings) const
{
    settings.beginGroup(QStringLiteral("device_view"));
    settings.setValue(QStringLiteral("view_header_geometry"), _view.header()->saveGeometry());
    settings.setValue(QStringLiteral("view_header_state"), _view.header()->saveState());
    settings.endGroup();
}

void DeviceView::restoreSettings(QSettings &settings)
{
    settings.beginGroup(QStringLiteral("device_view"));
    _view.header()->restoreGeometry(settings.value(QStringLiteral("view_header_geometry")).toByteArray());
    _view.header()->restoreState(settings.value(QStringLiteral("view_header_state")).toByteArray());
    settings.endGroup();
}

void DeviceView::onDoubleClicked(QModelIndex const &index)
{
    if (!index.isValid())
        return;

    auto const type = index.data(SlaveItemModel::RoleItemType).toString();
    if (type == QStringLiteral("RESPONDENT_PLACE"))
        return;

    auto const id = index.data(SlaveItemModel::RoleItemId).toUuid();
    emit doubleClicked(id, type);
}
