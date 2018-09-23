#ifndef MEDIA_PLAYER_EDITOR_H
#define MEDIA_PLAYER_EDITOR_H

#include <QComboBox>
#include <QLabel>
#include <QListView>
#include <default_base_editor.h>
#include <message_router.h>
#include "files_model.h"

class MediaPlayerEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit MediaPlayerEditor(EditorData const &data, QWidget &parent);

public:
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;
    QStringList errors() const override;

private:
    void onViewClicked(QModelIndex const &index);
    void onMessage(Message const &message);
    void onDisplays(Message const &message);

private:
    MessageRouter _router;
    QLabel _displaysLabel;
    QComboBox _displays;
    QLabel _mediaFilesLabel;
    QListView _mediaFiles;
    FilesModel _filesModel;
};

#endif // MEDIA_PLAYER_EDITOR_H
