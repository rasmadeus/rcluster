#include <QJsonArray>
#include <QJsonObject>
#include <QFileDialog>
#include <QVBoxLayout>
#include <globals.h>
#include <config.h>
#include <corebus.h>
#include <message.h>
#include "media_player_editor.h"

MediaPlayerEditor::MediaPlayerEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
    , _displaysLabel{ tr("Show video on display:"), this }
    , _displays{ this }
    , _mediaFilesLabel{ tr("Media files:"), this }
    , _mediaFiles{ this }
{
    _displays.addItem(tr("No data"));
    _displays.setEnabled(false);

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

    _router.handle(QStringLiteral("DISPLAYS"), std::bind(&MediaPlayerEditor::onDisplays, this, std::placeholders::_1));

    connect(&_mediaFiles, &QListView::clicked, this, &MediaPlayerEditor::onViewClicked);
    connect(&_corebus, &Corebus::ready, this, &MediaPlayerEditor::onMessage);

    auto computer = _config.parent(_id, QStringLiteral("COMPUTER"));
    _corebus.send(QStringLiteral("GET_DISPLAYS"), computer.toString());
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

void MediaPlayerEditor::onViewClicked(QModelIndex const &index)
{
    if (!index.isValid())
        return;

    static auto const filter = tr("Video files (*.avi *.flv *wmv *mov *mp4);; All files (*.*)");
    auto const currentPath = index.data(FilesModel::RolePath).toString();
    auto const newPath = QFileDialog::getOpenFileName(this, tr("Add media file"), currentPath, filter);
    if (!newPath.isEmpty())
        _filesModel.setData(index, newPath);
}

void MediaPlayerEditor::onMessage(Message const &message)
{
    _router.route(message);
}

void MediaPlayerEditor::onDisplays(Message const &message)
{
    _displays.clear();

    for(auto value : message.param(QStringLiteral("displays")).toJsonArray())
    {
        auto const object = value.toObject();
        auto const index = object.value(QStringLiteral("display_index"));
        _displays.addItem(tr("Display: %1").arg(index.toInt()), index);
    }

    if (_displays.count() == 0)
        _displays.addItem(tr("No data"));
}
