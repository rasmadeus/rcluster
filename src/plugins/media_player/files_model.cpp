#include <QFileInfo>
#include <QIcon>
#include <QMimeDatabase>
#include <QMimeType>
#include "files_model.h"

FilesModel::FilesModel(QObject *parent)
    : QAbstractListModel{ parent }
{
}

int FilesModel::rowCount(QModelIndex const &parent) const
{
    Q_UNUSED(parent)
    return _files.size() + 1;
}

QVariant FilesModel::data(QModelIndex const &index, int role) const
{
    if (!index.isValid())
        return {};

    if (index.row() == _files.size())
    {
        if (role == Qt::DisplayRole)
            return tr("Press this row, to append a new media file...");
        return {};
    }

    switch(role)
    {
        case Qt::ToolTip:
        case RolePath: return _files[index.row()];
        case Qt::DecorationRole: return dataDecoration(index);
        case Qt::DisplayRole: return QFileInfo{ _files[index.row()] }.fileName();
        default: return {};
    }
}

QVariant FilesModel::dataDecoration(QModelIndex const &index) const
{

    auto const mimeType = _mimeDatabase.mimeTypeForFile(_files[index.row()]);
    if (!mimeType.isValid())
        return {};

    auto icon = QIcon::fromTheme(mimeType.iconName());
    if (icon.isNull())
        icon = QIcon::fromTheme(mimeType.genericIconName());

    if (icon.isNull())
        return {};

    return icon;
}
