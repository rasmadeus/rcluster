#include <QFileInfo>
#include <QIcon>
#include <QMimeDatabase>
#include <QMimeType>
#include "files_model.h"

FilesModel::FilesModel(QObject *parent)
    : QAbstractListModel{ parent }
{
    appendEmptyRow();
}

int FilesModel::rowCount(QModelIndex const &parent) const
{
    Q_UNUSED(parent)
    return _files.size();
}

QVariant FilesModel::data(QModelIndex const &index, int role) const
{
    if (!index.isValid())
        return {};

    switch(role)
    {
        case Qt::ToolTipRole:
        case RolePath: return _files[index.row()];
        case Qt::DecorationRole: return dataDecoration(index);
        case Qt::DisplayRole: return dataDisplay(index);
        default: return {};
    }
}

bool FilesModel::setData(QModelIndex const &index, QVariant const &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    _files[index.row()] = value.toString();
    emit dataChanged(index, index);

    if (index.row() == _files.size() - 1)
        appendEmptyRow();

    return true;
}

QVariant FilesModel::dataDisplay(QModelIndex const &index) const
{
    auto const path = _files[index.row()];
    return path.isEmpty() ? tr("Add new file...") : QFileInfo{ path }.fileName();
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

void FilesModel::appendEmptyRow()
{
    beginInsertRows({}, _files.size(), _files.size());
    _files << QString{};
    endInsertRows();
}