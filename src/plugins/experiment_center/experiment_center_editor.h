#ifndef EXPERIMENT_CENTER_EDITOR_H
#define EXPERIMENT_CENTER_EDITOR_H

#include <QLabel>
#include <QTreeView>
#include <data_combo_box.h>
#include <default_base_editor.h>
#include <slave_check_model.h>
#include <slave_type_proxy_model.h>

class ExperimentCenterEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit ExperimentCenterEditor(EditorData const &data, QWidget &parent);

public:
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;
    QStringList errors() const override;

private:
    void onTreeViewClicked(QModelIndex const &index);
    void onConfigChanged();

private:
    QLabel _mediaPlayerLabel;
    DataComboBox _mediaPlayers;
    QLabel _viewLabel;
    QTreeView _view;
    SlaveCheckModel _model;
    SlaveTypeProxyModel _proxyModel;
};

#endif // EXPERIMENT_CENTER_EDITOR_H
