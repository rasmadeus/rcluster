#ifndef MESSAGE_VIEWER_EDITOR_H
#define MESSAGE_VIEWER_EDITOR_H

#include <QPushButton>
#include <QLabel>
#include <QTreeView>
#include <default_base_editor.h>
#include <slave_model_check.h>

class SlaveProxyCheckModel;

class MessageViewerEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit MessageViewerEditor(QWidget &parent);

public:
    void init() override;
    SlaveAsParams slaveAsParams() const override { return { QStringLiteral("slaves"), _slaveModel->checked() } ; }
    void setSlaveAsParams(SlaveAsParams const &slaveAsParams) override;

private:
    void onTreeViewClicked(QModelIndex const &index);
    void onConfigChanged();

private:
    QLabel _captionLabel;
    QTreeView _treeView;
    QPushButton _selectAll;
    QPushButton _deselectAll;
    SlaveModelCheck *_slaveModel{ nullptr };
    SlaveProxyCheckModel *_slaveProxyModel{ nullptr };
};

#endif // MESSAGE_VIEWER_EDITOR_H
