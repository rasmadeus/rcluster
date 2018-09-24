#include <QHeaderView>
#include <QVBoxLayout>
#include <globals.h>
#include "experiment_center_editor.h"

ExperimentCenterEditor::ExperimentCenterEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
    , _mediaPlayerLabel{ tr("Select Media Player:"), this }
    , _mediaPlayers{ this }
    , _viewLabel{ tr("Select respondent places:"), this }
    , _model{ _config, _plugins, *this }
    , _proxyModel{ { QStringLiteral("RESPONDENT_PLACES"), }, { QStringLiteral("RESPONDENT_PLACE"), }, *this }
{
    _mediaPlayers.fillWithLocals(_config, QStringLiteral("MEDIA_PLAYER"), _id);
    _proxyModel.setSourceModel(&_model);

    _view.header()->hide();
    _view.setModel(&_proxyModel);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->setMargin(0);
    mainLayout->addWidget(&_mediaPlayerLabel);
    mainLayout->addWidget(&_mediaPlayers);
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
        { QStringLiteral("media_player"), QVariantList{ _mediaPlayers.currentData(), } },
        { QStringLiteral("respondent_places"), _model.checked() },
    };
}

void ExperimentCenterEditor::setParams(QVariantHash const &params)
{
    _mediaPlayers.setIndex(params.value(QStringLiteral("media_player")).toList());
    _model.setChecked(params.value(QStringLiteral("respondent_places")).toList());
    _view.expandAll();
}

QStringList ExperimentCenterEditor::errors() const
{
    QStringList errors;
    if (!_mediaPlayers.currentData().isValid())
        errors << tr("You have to select a Media Player. If you can't - create one.");
    return errors;
}

void ExperimentCenterEditor::onTreeViewClicked(QModelIndex const &index)
{
    _proxyModel.setData(index, {}, SlaveCheckModel::RoleToggleCheckState);
}

void ExperimentCenterEditor::onConfigChanged()
{
    _proxyModel.sort(SlaveModel::ColumnCaption);
    _proxyModel.invalidate();
}
