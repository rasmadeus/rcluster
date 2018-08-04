#ifndef MESSAGE_VIEWER_EDITOR_H
#define MESSAGE_VIEWER_EDITOR_H

#include <QPushButton>
#include <QLabel>
#include <QTreeView>
#include <default_base_editor.h>
#include <slave_model_check.h>

class MessageViewerEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit MessageViewerEditor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent);

public:
    QSet<QUuid> events() const override { return _slaveModel.checked(); }
    void setEvents(QSet<QUuid> const &events) override;

private:
    void onTreeViewClicked(QModelIndex const &index);

private:
    QLabel _captionLabel;
    QTreeView _treeView;
    QPushButton _selectAll;
    QPushButton _deselectAll;
    SlaveModelCheck _slaveModel;
};

#endif // MESSAGE_VIEWER_EDITOR_H
