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
    Qt::ItemFlags flags(QModelIndex const &index) const override;
    int rowCount(QModelIndex const &parent = {}) const override;
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;
    bool setData(QModelIndex const &index, QVariant const &value, int role = Qt::EditRole) override;

public:
    QStringList const files() const { return _files; }
    void setFiles(QStringList const &files);

private:
    QVariant dataDisplay(QModelIndex const &index) const;
    QVariant dataDecoration(QModelIndex const &index) const;
    QVariant dataFont(QModelIndex const &index) const;
    void appendEmptyRow();

private:
    QStringList _files;
    QMimeDatabase _mimeDatabase;
};

#endif // FILES_MODEL_H
