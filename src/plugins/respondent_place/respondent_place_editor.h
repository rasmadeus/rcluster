#ifndef RESPONDENT_PLACE_EDITOR_H
#define RESPONDENT_PLACE_EDITOR_H

#include <QLabel>
#include <QTreeView>
#include <default_base_editor.h>
#include <slave_sort_model.h>
#include "device_model.h"

class RespondentPlaceEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit RespondentPlaceEditor(EditorData const &data, QWidget &parent);

public:
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;

private:
    void onTreeViewClicked(QModelIndex const &index);
    void onConfigChanged();

private:
    QLabel _deviceViewLabel;
    QTreeView _deviceView;
    DeviceModel _model;
    SlaveSortModel _sortModel;
};

#endif // RESPONDENT_PLACE_EDITOR_H
