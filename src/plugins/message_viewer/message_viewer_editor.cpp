#include <QHeaderView>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <config.h>
#include <globals.h>
#include <slave_sort_model.h>
#include "message_viewer_editor.h"

MessageViewerEditor::MessageViewerEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
    , _captionLabel{ tr("Watch objects:")}
    , _treeView{ this }
    , _selectAll{ tr("Select all"), this }
    , _deselectAll{ tr("Deselect all"), this }
{
    _slaveModel = new SlaveModelCheck{ _config, _plugins, *this };

    _slaveSortModel = new SlaveSortModel{ *this };
    _slaveSortModel->setSourceModel(_slaveModel);

    _treeView.header()->hide();
    _treeView.setSelectionBehavior(QAbstractItemView::SelectRows);
    _treeView.setSelectionMode(QAbstractItemView::SingleSelection);
    _treeView.setModel(_slaveSortModel);

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

    connect(_slaveModel, &SlaveModel::rowsInserted, this, &MessageViewerEditor::onConfigChanged);
    connect(_slaveModel, &SlaveModel::dataChanged, this, &MessageViewerEditor::onConfigChanged);

    connect(&_treeView, &QTreeView::clicked, this, &MessageViewerEditor::onTreeViewClicked);
    connect(&_selectAll, &QPushButton::clicked, _slaveModel, &SlaveModelCheck::selectAll);
    connect(&_deselectAll, &QPushButton::clicked, _slaveModel, &SlaveModelCheck::deselectAll);

    onConfigChanged();
}

void MessageViewerEditor::onTreeViewClicked(QModelIndex const &index)
{
    _slaveModel->setData(_slaveSortModel->mapToSource(index), {}, SlaveModelCheck::RoleToggleCheckState);
}

void MessageViewerEditor::onConfigChanged()
{
    _slaveSortModel->sort(SlaveModel::ColumnCaption);
    _slaveSortModel->invalidate();
}

QVariantHash MessageViewerEditor::params() const
{
    QVariantList slaves;
    for(auto &&id : _slaveModel->checked())
        slaves << std::move(id);

    return {
        { QStringLiteral("slaves"), slaves },
    };
}

void MessageViewerEditor::setParams(QVariantHash const &params)
{
    QSet<QUuid> slaves;
    for(auto const &id : params.value(QStringLiteral("slaves")).toList())
        slaves << id.toUuid();

    _slaveModel->setChecked(slaves);
    _treeView.expandAll();
}
