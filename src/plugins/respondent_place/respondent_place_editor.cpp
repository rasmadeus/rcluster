#include <QHeaderView>
#include <QVBoxLayout>
#include <globals.h>
#include "respondent_place_editor.h"

RespondentPlaceEditor::RespondentPlaceEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
    , _placeNumberLabel{ tr("Input a respondent's place number:") }
    , _deviceViewLabel{ tr("Select devices:"), this }
    , _model{ _config, _plugins, *this }
    , _proxyModel{ { QStringLiteral("COMPUTER"), QStringLiteral("CAMERAS"), }, { QStringLiteral("CAMERA"), }, *this }
{
    _placeNumber.setMinimum(1);

    _proxyModel.setSourceModel(&_model);
    _deviceView.setModel(&_proxyModel);
    _deviceView.header()->hide();

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_placeNumberLabel);
    mainLayout->addWidget(&_placeNumber);
    mainLayout->addWidget(&_deviceViewLabel);
    mainLayout->addWidget(&_deviceView);

    onConfigChanged();

    connect(&_model, &SlaveCheckModel::rowsInserted, this, &RespondentPlaceEditor::onConfigChanged);
    connect(&_model, &SlaveCheckModel::dataChanged, this, &RespondentPlaceEditor::onConfigChanged);
    connect(&_deviceView, &QTreeView::clicked, this, &RespondentPlaceEditor::onTreeViewClicked);
}

QVariantHash RespondentPlaceEditor::params() const
{
    return {
        { QStringLiteral("place_number"), _placeNumber.value() },
        { QStringLiteral("devices"), _model.checked() },
    };
}

void RespondentPlaceEditor::setParams(QVariantHash const &params)
{
    _placeNumber.setValue(params.value(QStringLiteral("place_number")).toInt());
    _model.setChecked(params.value(QStringLiteral("devices")).toList());
    _deviceView.expandAll();
}

void RespondentPlaceEditor::onTreeViewClicked(QModelIndex const &index)
{
    _proxyModel.setData(index, {}, SlaveCheckModel::RoleToggleCheckState);
}

void RespondentPlaceEditor::onConfigChanged()
{
    _proxyModel.sort(SlaveModel::ColumnCaption);
    _proxyModel.invalidate();
}
