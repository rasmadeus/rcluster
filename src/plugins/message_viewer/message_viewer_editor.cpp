#include <QHeaderView>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <config.h>
#include <globals.h>
#include <node_sort_model.h>
#include "message_viewer_editor.h"

MessageViewerEditor::MessageViewerEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
    , _captionLabel{ tr("Watch objects:")}
    , _treeView{ this }
    , _selectAll{ tr("Select all"), this }
    , _deselectAll{ tr("Deselect all"), this }
{
    _nodeModel = new NodeCheckModel{ _config, _plugins, *this };

    _nodeSortModel = new NodeSortModel{ *this };
    _nodeSortModel->setSourceModel(_nodeModel);

    _treeView.header()->hide();
    _treeView.setSelectionBehavior(QAbstractItemView::SelectRows);
    _treeView.setSelectionMode(QAbstractItemView::SingleSelection);
    _treeView.setModel(_nodeSortModel);

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

    connect(_nodeModel, &NodeModel::rowsInserted, this, &MessageViewerEditor::onConfigChanged);
    connect(_nodeModel, &NodeModel::dataChanged, this, &MessageViewerEditor::onConfigChanged);

    connect(&_treeView, &QTreeView::clicked, this, &MessageViewerEditor::onTreeViewClicked);
    connect(&_selectAll, &QPushButton::clicked, _nodeModel, &NodeCheckModel::selectAll);
    connect(&_deselectAll, &QPushButton::clicked, _nodeModel, &NodeCheckModel::deselectAll);

    onConfigChanged();
}

void MessageViewerEditor::onTreeViewClicked(QModelIndex const &index)
{
    _nodeModel->setData(_nodeSortModel->mapToSource(index), {}, NodeCheckModel::RoleToggleCheckState);
}

void MessageViewerEditor::onConfigChanged()
{
    _nodeSortModel->sort(NodeModel::ColumnCaption);
    _nodeSortModel->invalidate();
}

QVariantHash MessageViewerEditor::params() const
{
    return {
        { QStringLiteral("nodes"), _nodeModel->checked() },
    };
}

void MessageViewerEditor::setParams(QVariantHash const &params)
{
    _nodeModel->setChecked(params.value(QStringLiteral("nodes")).toList());
    _treeView.expandAll();
}
