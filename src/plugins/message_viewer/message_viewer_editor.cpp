#include <QHeaderView>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <globals.h>
#include "message_viewer_editor.h"

MessageViewerEditor::MessageViewerEditor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent)
    : DefaultBaseEditor{ config, plugins, socket, id, parent }
    , _captionLabel{ tr("Watch objects:")}
    , _treeView{ this }
    , _selectAll{ tr("Select all"), this }
    , _deselectAll{ tr("Deselect all"), this }
    , _slaveModel{ config, plugins, *this }
{
    _slaveModel.setSlave(id);

    _treeView.header()->hide();
    _treeView.setSelectionBehavior(QAbstractItemView::SelectRows);
    _treeView.setSelectionMode(QAbstractItemView::SingleSelection);
    _treeView.setModel(&_slaveModel);

    auto buttonsLayout = new QHBoxLayout{};
    buttonsLayout->setMargin(0);
    buttonsLayout->setSpacing(rcluster::layoutGap());
    buttonsLayout->addWidget(&_selectAll);
    buttonsLayout->addWidget(&_deselectAll);
    buttonsLayout->addSpacerItem(new QSpacerItem{ 0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum });

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_captionLabel);
    mainLayout->addWidget(&_treeView);
    mainLayout->addLayout(buttonsLayout);

    connect(&_treeView, &QTreeView::clicked, this, &MessageViewerEditor::onTreeViewClicked);
    connect(&_selectAll, &QPushButton::clicked, &_slaveModel, &SlaveModelCheck::selectAll);
    connect(&_deselectAll, &QPushButton::clicked, &_slaveModel, &SlaveModelCheck::deselectAll);
}

void MessageViewerEditor::onTreeViewClicked(QModelIndex const &index)
{
    _slaveModel.setData(index, {}, SlaveModelCheck::RoleToggleCheckState);
}

void MessageViewerEditor::setEvents(QSet<QUuid> const &events)
{
    _slaveModel.setChecked(events);
    _treeView.expandAll();
}
