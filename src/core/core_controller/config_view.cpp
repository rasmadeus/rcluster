#include <QHeaderView>
#include <QMenu>
#include <QVBoxLayout>
#include <QUuid>
#include <QTimer>
#include <config.h>
#include <core_client_socket.h>
#include <globals.h>
#include <plugins.h>
#include "config_view.h"
#include "name_dialog.h"

ConfigView::ConfigView(Config &config, Plugins &plugins, CoreClientSocket &socket, QWidget &parent)
    : QWidget{ &parent }
    , _view{ this }
    , _model{ config, plugins, *this }
    , _sortModel{ *this }
    , _menuController{ config, plugins, socket, *this }
    , _config{ config }
    , _plugins{ plugins }
    , _socket{ socket }
{
    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(rcluster::layoutGap());
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_view);

    _view.header()->hide();
    _view.setSelectionBehavior(QAbstractItemView::SelectRows);
    _view.setSelectionMode(QAbstractItemView::SingleSelection);
    _view.setModel(&_sortModel);
    _view.setContextMenuPolicy(Qt::CustomContextMenu);

    connect(&_view, &QTreeView::customContextMenuRequested, this, &ConfigView::showMenu);
    connect(_view.selectionModel(), &QItemSelectionModel::currentChanged, this, &ConfigView::select);
    connect(&_model, &SlaveModel::rowsRemoved, this, &ConfigView::selectCurrent);
    connect(&_model, &SlaveModel::rowsInserted, &_sortModel, &SlaveSortModel::invalidate);
    connect(&_model, &SlaveModel::dataChanged, &_sortModel, &SlaveSortModel::invalidate);
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

void ConfigView::selectCurrent()
{
    qDebug() << "Current:" << _view.currentIndex().data(SlaveModel::RoleItemId).toUuid();
}
