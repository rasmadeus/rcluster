#ifndef FILES_MODEL_H
#define FILES_MODEL_H

#include <QAbstractListModel>
#include <QMimeDatabase>

class FilesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum
    {
        RolePath = Qt::UserRole + 1,
    };

public:
    explicit FilesModel(QObject *parent = nullptr);

public:
    int rowCount(QModelIndex const &parent = {}) const override;
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;

private:
    QVariant dataDecoration(QModelIndex const &index) const;

private:
    QStringList _files;
    QMimeDatabase _mimeDatabase;
};

#endif // FILES_MODEL_H
