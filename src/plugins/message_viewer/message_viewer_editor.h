#ifndef MESSAGE_VIEWER_EDITOR_H
#define MESSAGE_VIEWER_EDITOR_H

#include <QPushButton>
#include <QLabel>
#include <QTreeView>
#include <default_base_editor.h>
#include <node_check_model.h>

class NodeSortModel;

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
    NodeCheckModel *_nodeModel{ nullptr };
    NodeSortModel *_nodeSortModel{ nullptr };
};

#endif // MESSAGE_VIEWER_EDITOR_H
