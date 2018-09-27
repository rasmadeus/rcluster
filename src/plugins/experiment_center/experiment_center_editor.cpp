#include <QHeaderView>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QJsonObject>
#include <QVBoxLayout>
#include <corebus.h>
#include <message.h>
#include <globals.h>
#include "experiment_center_editor.h"

ExperimentCenterEditor::ExperimentCenterEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
    , _mediaPlayerLabel{ tr("Select Media Player:"), this }
    , _mediaPlayer{ this }
    , _labRestApiLabel{ tr("Select Labaratory Rest Api:"), this }
    , _labRestApi{ this }
    , _viewLabel{ tr("Select respondent places:"), this }
    , _model{ _config, _plugins, *this }
    , _proxyModel{ { QStringLiteral("RESPONDENT_PLACES"), }, { QStringLiteral("RESPONDENT_PLACE"), }, *this }
{
    _mediaPlayer.fillWithLocals(_config, QStringLiteral("MEDIA_PLAYER"), _id);
    _labRestApi.fillWithLocals(_config, QStringLiteral("LAB_REST_API"), _id);
    _proxyModel.setSourceModel(&_model);

    _view.header()->hide();
    _view.setModel(&_proxyModel);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->setMargin(0);
    mainLayout->addWidget(&_mediaPlayerLabel);
    mainLayout->addWidget(&_mediaPlayer);
    mainLayout->addWidget(&_labRestApiLabel);
    mainLayout->addWidget(&_labRestApi);
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
        { QStringLiteral("media_player"), QVariantList{ _mediaPlayer.currentData(), } },
        { QStringLiteral("lab_rest_api"), QVariantList{ _labRestApi.currentData(), } },
        { QStringLiteral("respondent_places"), _model.checked() },
    };
}

void ExperimentCenterEditor::setParams(QVariantHash const &params)
{
    _labRestApi.setIndex(params.value(QStringLiteral("lab_rest_api")).toList());
    _mediaPlayer.setIndex(params.value(QStringLiteral("media_player")).toList());
    _model.setChecked(params.value(QStringLiteral("respondent_places")).toList());
    _view.expandAll();
}

QStringList ExperimentCenterEditor::errors() const
{
    QStringList errors;
    if (!_mediaPlayer.currentData().isValid())
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
