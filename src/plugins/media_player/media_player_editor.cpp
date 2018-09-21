#include <QVBoxLayout>
#include <globals.h>
#include "media_player_editor.h"

MediaPlayerEditor::MediaPlayerEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
    , _displaysLabel{ tr("Display:"), this }
    , _displays{ this }
    , _mediaFilesLabel{ tr("Media files:"), this }
    , _mediaFiles{ this }
{
    _mediaFiles.setModel(&_filesModel);
    _mediaFiles.setSelectionBehavior(QAbstractItemView::SelectRows);
    _mediaFiles.setSelectionMode(QAbstractItemView::SingleSelection);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_displaysLabel);
    mainLayout->addWidget(&_displays);
    mainLayout->addWidget(&_mediaFilesLabel);
    mainLayout->addWidget(&_mediaFiles);
}

QVariantHash MediaPlayerEditor::params() const
{
    return {};
}

void MediaPlayerEditor::setParams(QVariantHash const &params)
{
}

QStringList MediaPlayerEditor::errors() const
{
    QStringList errors;
    return errors;
}
