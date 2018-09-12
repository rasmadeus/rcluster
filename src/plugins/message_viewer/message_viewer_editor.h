#ifndef MESSAGE_VIEWER_EDITOR_H
#define MESSAGE_VIEWER_EDITOR_H

#include <QPushButton>
#include <QLabel>
#include <QTreeView>
#include <default_base_editor.h>
#include <slave_model_check.h>

class SlaveSortModel;

class MessageViewerEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit MessageViewerEditor(EditorData const &data, QWidget &parent);

public:
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;

private:
    void onTreeViewClicked(QModelIndex const &index);
    void onConfigChanged();

private:
    QLabel _captionLabel;
    QTreeView _treeView;
    QPushButton _selectAll;
    QPushButton _deselectAll;
    SlaveModelCheck *_slaveModel{ nullptr };
    SlaveSortModel *_slaveSortModel{ nullptr };
};

#endif // MESSAGE_VIEWER_EDITOR_H
