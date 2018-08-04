#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <storable.h>
#include "file_storable.h"

FileStorable::FileStorable(QString const &path)
    : _path { path }
{
}

void FileStorable::store(Storable const &storable)
{
    QFile file{ _path };
    if (file.open(QIODevice::WriteOnly))
    {
        auto const data = QJsonDocument{ storable.toJson() }.toJson();
        qDebug() << "It's about to store data with size: " << data.size() << " bytes.";
        auto const writtenBytes = file.write(data);
        qDebug() << "Data has been stored with size: " << writtenBytes << " bytes.";
    }
    else
    {
        qCritical() << "Failed to store data into file " << _path << ".";
    }
}

void FileStorable::restore(Storable &storable)
{
    QFile file{ _path };

    if (!file.exists())
    {
        qWarning() << "Failed to restore data due to file " << _path << " isn't exists.";
        return;
    }

    if (file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File " << _path << "has been opened.";
        storable.fromJson(QJsonDocument::fromJson(file.readAll()).object());
    }
    else
    {
        qCritical() << "Failed to restore data from file " << _path << ".";
    }
}
