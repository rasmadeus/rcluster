#include <QHeaderView>
#include <QVBoxLayout>
#include <globals.h>
#include "experiment_center_editor.h"

ExperimentCenterEditor::ExperimentCenterEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
    , _viewLabel{ tr("Select respondent places:"), this }
    , _model{ _config, _plugins, *this }
    , _proxyModel{ { QStringLiteral("RESPONDENT_PLACES"), }, { QStringLiteral("RESPONDENT_PLACE"), }, *this }
{
    _proxyModel.setSourceModel(&_model);

    _view.header()->hide();
    _view.setModel(&_proxyModel);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->setMargin(0);
    mainLayout->addWidget(&_viewLabel);
    mainLayout->addWidget(&_view);

    onConfigChanged();

    connect(&_model, &SlaveCheckModel::rowsInserted, this, &ExperimentCenterEditor::onConfigChanged);
    connect(&_model, &SlaveCheckModel::dataChanged, this, &ExperimentCenterEditor::onConfigChanged);
    connect(&_view, &QTreeView::clicked, this, &ExperimentCenterEditor::onTreeViewClicked);
}

QVariantHash ExperimentCenterEditor::params() const
{
    return {
        { QStringLiteral("respondent_places"), _model.checked() },
    };
}

void ExperimentCenterEditor::setParams(QVariantHash const &params)
{
    _model.setChecked(params.value(QStringLiteral("respondent_places")).toList());
    _view.expandAll();
}

void ExperimentCenterEditor::onTreeViewClicked(QModelIndex const &index)
{
    _model.setData(_proxyModel.mapToSource(index), {}, SlaveCheckModel::RoleToggleCheckState);
}

void ExperimentCenterEditor::onConfigChanged()
{
    _proxyModel.sort(SlaveModel::ColumnCaption);
    _proxyModel.invalidate();
}
