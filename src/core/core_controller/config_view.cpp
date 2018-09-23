#include <QHeaderView>
#include <QMenu>
#include <QVBoxLayout>
#include <QUuid>
#include <QTimer>
#include <config.h>
#include <corebus.h>
#include <globals.h>
#include <plugins.h>
#include "config_view.h"
#include "name_dialog.h"

ConfigView::ConfigView(Config &config, Plugins &plugins, Corebus &corebus, QWidget &parent)
    : QWidget{ &parent }
    , _view{ this }
    , _model{ config, plugins, *this }
    , _sortModel{ *this }
    , _menuController{ config, plugins, corebus, *this }
    , _config{ config }
    , _plugins{ plugins }
    , _corebus{ corebus }
{
    _sortModel.setSourceModel(&_model);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_view);

    _view.header()->hide();
    _view.setSelectionBehavior(QAbstractItemView::SelectRows);
    _view.setSelectionMode(QAbstractItemView::SingleSelection);
    _view.setModel(&_sortModel);
    _view.setContextMenuPolicy(Qt::CustomContextMenu);

    connect(&_view, &QTreeView::customContextMenuRequested, this, &ConfigView::showMenu);
    connect(_view.selectionModel(), &QItemSelectionModel::currentChanged, this, &ConfigView::select);
    connect(&_model, &SlaveModel::reloaded, &_view, &QTreeView::expandAll);
    connect(&_model, &SlaveModel::rowsInserted, this, &ConfigView::sortSlaves);
    connect(&_model, &SlaveModel::rowsInserted, this, &ConfigView::trySelectLast);
    connect(&_model, &SlaveModel::renamed, this, &ConfigView::sortSlaves);
    connect(&_model, &SlaveModel::reloaded, this, &ConfigView::sortSlaves);

    sortSlaves();
}

void ConfigView::showMenu(QPoint const &pos)
{
    QMenu menu{ this };
    _menuController.watch(menu, _view.indexAt(pos).data(SlaveModel::RoleItemId).toUuid());
    menu.exec(_view.mapToGlobal(pos));
}

void ConfigView::select(QModelIndex const &current)
{
    auto const id = current.data(SlaveModel::RoleItemId).toUuid();
    emit selected(id);
}

void ConfigView::sortSlaves()
{
    _view.expandAll();
    _sortModel.sort(SlaveModel::ColumnCaption);
}

void ConfigView::trySelectLast(QModelIndex const &parent, int first, int last)
{
    Q_UNUSED(first)
    auto const index = _model.index(last, SlaveItemModel::ColumnCaption, parent);
    auto const id = index.data(SlaveModel::RoleItemId).toUuid();
    if (!id.isNull() && _menuController.last() == id)
    {
        _view.selectionModel()->select(_sortModel.mapFromSource(index), QItemSelectionModel::ClearAndSelect);
        emit selected(id);
    }
}
