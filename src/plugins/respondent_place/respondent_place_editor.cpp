#include <QHeaderView>
#include <QVBoxLayout>
#include <globals.h>
#include "respondent_place_editor.h"

RespondentPlaceEditor::RespondentPlaceEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
    , _deviceViewLabel{ tr("Select devices:"), this }
    , _model{ _config, _plugins, *this }
    , _sortModel{ *this }
{
    _sortModel.setSourceModel(&_model);
    _deviceView.setModel(&_sortModel);
    _deviceView.header()->hide();

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_deviceViewLabel);
    mainLayout->addWidget(&_deviceView);

    onConfigChanged();

    connect(&_model, &DeviceModel::rowsInserted, this, &RespondentPlaceEditor::onConfigChanged);
    connect(&_model, &DeviceModel::dataChanged, this, &RespondentPlaceEditor::onConfigChanged);
     connect(&_deviceView, &QTreeView::clicked, this, &RespondentPlaceEditor::onTreeViewClicked);
}

QVariantHash RespondentPlaceEditor::params() const
{
    return {};
}

void RespondentPlaceEditor::setParams(QVariantHash const &params)
{

}

void RespondentPlaceEditor::onTreeViewClicked(QModelIndex const &index)
{
    _model.setData(_sortModel.mapToSource(index), {}, SlaveModelCheck::RoleToggleCheckState);
}

void RespondentPlaceEditor::onConfigChanged()
{
    _model.sort(SlaveModel::ColumnCaption);
}
