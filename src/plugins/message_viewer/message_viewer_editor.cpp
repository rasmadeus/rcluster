#include <QHeaderView>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <config.h>
#include <globals.h>
#include <slave_proxy_check_model.h>
#include "message_viewer_editor.h"

MessageViewerEditor::MessageViewerEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
    , _captionLabel{ tr("Watch objects:")}
    , _treeView{ this }
    , _selectAll{ tr("Select all"), this }
    , _deselectAll{ tr("Deselect all"), this }
{
    _slaveModel = new SlaveModelCheck{ data.config, data.plugins, *this };
    _slaveModel->setSlave(data.id);
    _slaveModel->setChecked(data.config.slave(data.id).slaveAsParams().slaves(QStringLiteral("slaves")));

    _slaveProxyModel = new SlaveProxyCheckModel{ *this };
    _slaveProxyModel->setSourceModel(_slaveModel);
    _slaveProxyModel->setSlaveId(data.id);

    _treeView.header()->hide();
    _treeView.setSelectionBehavior(QAbstractItemView::SelectRows);
    _treeView.setSelectionMode(QAbstractItemView::SingleSelection);
    _treeView.setModel(_slaveProxyModel);

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
    _slaveModel->setData(_slaveProxyModel->mapToSource(index), {}, SlaveModelCheck::RoleToggleCheckState);
}

void MessageViewerEditor::onConfigChanged()
{
    _slaveProxyModel->sort(SlaveModel::ColumnCaption);
    _slaveProxyModel->invalidate();
}

void MessageViewerEditor::setSlaveAsParams(SlaveAsParams const &slaveAsParams)
{
    _slaveModel->setChecked(slaveAsParams.slaves(QStringLiteral("slaves")));
    _treeView.expandAll();
}
