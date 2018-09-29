#include <QHeaderView>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QJsonObject>
#include <QVBoxLayout>
#include <corebus.h>
#include <message.h>
#include <globals.h>
#include "experiment_center_editor.h"

namespace
{
    QJsonArray getExperimentParams()
    {
        static auto const collectingStatus = QStringLiteral("1");
        return {
            QJsonObject{ { QStringLiteral("key"), QStringLiteral("limit") }, { QStringLiteral("value"), QStringLiteral("200") }, },
            QJsonObject{ { QStringLiteral("key"), QStringLiteral("status") }, { QStringLiteral("value"), collectingStatus }, },
        };
    }

    QJsonArray getSausageParams(QString const &experiment)
    {
        static auto const collectingStatus = QStringLiteral("1");
        return {
            QJsonObject{ { QStringLiteral("key"), QStringLiteral("limit") }, { QStringLiteral("value"), QStringLiteral("200") }, },
            QJsonObject{ { QStringLiteral("key"), QStringLiteral("experiment") }, { QStringLiteral("value"), experiment }, },
        };
    }
}

ExperimentCenterEditor::ExperimentCenterEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
    , _mediaPlayerLabel{ tr("Select Media Player:"), this }
    , _mediaPlayer{ this }
    , _labRestApiLabel{ tr("Select Labaratory Rest Api:"), this }
    , _experimentLabel{ tr("Select an experiment:"), this }
    , _sausageLabel{ tr("Select a sausage:"), this }
    , _viewLabel{ tr("Select respondent places:"), this }
    , _model{ _config, _plugins, *this }
    , _proxyModel{ { QStringLiteral("RESPONDENT_PLACES"), }, { QStringLiteral("RESPONDENT_PLACE"), }, *this }
{
    _router.handle(QStringLiteral("REPLY"), std::bind(&ExperimentCenterEditor::onReply, this, std::placeholders::_1));

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
    mainLayout->addWidget(&_experimentLabel);
    mainLayout->addWidget(&_experiment);
    mainLayout->addWidget(&_sausageLabel);
    mainLayout->addWidget(&_sausage);
    mainLayout->addWidget(&_viewLabel);
    mainLayout->addWidget(&_view);

    onConfigChanged();

    connect(&_model, &SlaveCheckModel::rowsInserted, this, &ExperimentCenterEditor::onConfigChanged);
    connect(&_model, &SlaveCheckModel::dataChanged, this, &ExperimentCenterEditor::onConfigChanged);
    connect(&_view, &QTreeView::clicked, this, &ExperimentCenterEditor::onTreeViewClicked);
    connect(&_labRestApi, static_cast<void(DataComboBox::*)(int)>(&DataComboBox::currentIndexChanged), this, &ExperimentCenterEditor::getExperiments);
    connect(&_experiment, static_cast<void(DataComboBox::*)(int)>(&DataComboBox::currentIndexChanged), this, &ExperimentCenterEditor::getSausages);
    connect(&_corebus, &Corebus::ready, this, &ExperimentCenterEditor::onMessage);
}

QVariantHash ExperimentCenterEditor::params() const
{
    return {
        { QStringLiteral("media_player"), QVariantList{ _mediaPlayer.currentData(), } },
        { QStringLiteral("lab_rest_api"), QVariantList{ _labRestApi.currentData(), } },
        { QStringLiteral("experiment"), _experiment.currentData() },
        { QStringLiteral("sausage"), _sausage.currentData() },
        { QStringLiteral("respondent_places"), _model.checked() },
    };
}

void ExperimentCenterEditor::setParams(QVariantHash const &params)
{
    _labRestApi.setIndex(params.value(QStringLiteral("lab_rest_api")).toList());
    _mediaPlayer.setIndex(params.value(QStringLiteral("media_player")).toList());
    _model.setChecked(params.value(QStringLiteral("respondent_places")).toList());
    _view.expandAll();

    getExperiments();
}

QStringList ExperimentCenterEditor::errors() const
{
    QStringList errors;
    if (!_mediaPlayer.currentData().isValid())
        errors << tr("You have to select a Media Player. If you can't - create one.");
    return errors;
}

void ExperimentCenterEditor::onTreeViewClicked(QModelIndex const &index)
{ExperimentCenterEditor::
    _proxyModel.setData(index, {}, SlaveCheckModel::RoleToggleCheckState);
}

void ExperimentCenterEditor::onConfigChanged()
{
    _proxyModel.sort(SlaveModel::ColumnCaption);
    _proxyModel.invalidate();
}

void ExperimentCenterEditor::onMessage(Message const &message)
{
    _router.route(message);
}

void ExperimentCenterEditor::onReply(Message const &message)
{
    if (_labRestApi.currentData().toUuid() != message.fromId())
        return;

    if (message.param(QStringLiteral("operation")).toInt() != QNetworkAccessManager::GetOperation)
        return;

    if (message.param(QStringLiteral("path")) == QStringLiteral("/core/api/experiment/"))
        fillExperiment(message);
    else if (message.param(QStringLiteral("path")) == QStringLiteral("/core/api/sausage/"))
        fillSausage(message);
}

void ExperimentCenterEditor::getExperiments()
{
    _experiment.clear();
    _experiment.addItem(tr("None"));

    _sausage.clear();
    _sausage.addItem(tr("None"));

    auto const labRestApiParam = _labRestApi.currentData();
    if (!labRestApiParam.isValid())
        return;

    _corebus.send(QStringLiteral("GET"), labRestApiParam.toString(), {
        { QStringLiteral("path"), QStringLiteral("experiment") },
        { QStringLiteral("params"), ::getExperimentParams() },
    });
}

void ExperimentCenterEditor::getSausages()
{
    _sausage.clear();
    _sausage.addItem(tr("None"));

    auto const labRestApiParam = _labRestApi.currentData();
    if (!labRestApiParam.isValid())
        return;

    auto const experiment = _experiment.currentData();
    if (!experiment.isValid())
        return;

    _corebus.send(QStringLiteral("GET"), labRestApiParam.toString(), {
        { QStringLiteral("path"), QStringLiteral("sausage") },
        { QStringLiteral("params"), ::getSausageParams(experiment.toString()) },
    });
}

void ExperimentCenterEditor::fillExperiment(Message const &message)
{
    for(auto const value : message.param(QStringLiteral("json")).toJsonObject().value(QStringLiteral("results")).toArray())
    {
        auto const record = value.toObject();
        _experiment.addItem(record.value(QStringLiteral("name")).toString(), record.value(QStringLiteral("id")));
    }

    _experiment.setIndex(_config.slave(_id).param(QStringLiteral("experiment")));

    getSausages();
}

void ExperimentCenterEditor::fillSausage(Message const &message)
{
    for(auto const value : message.param(QStringLiteral("json")).toJsonObject().value(QStringLiteral("results")).toArray())
    {
        auto const record = value.toObject();
        _sausage.addItem(record.value(QStringLiteral("name")).toString(), record.value(QStringLiteral("id")));
    }

    _sausage.setIndex(_config.slave(_id).param(QStringLiteral("sausage")));
}
