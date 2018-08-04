#ifndef QT_TYPES_HASH_H
#define QT_TYPES_HASH_H

#include <string>
#include <QUuid>
#include <QString>

class QStringHash
{
public:
    std::size_t operator () (QString const &var) const
    {
        return std::hash<std::string>{}(var.toStdString());
    }
};

class QUuidHash
{
public:
    std::size_t operator () (QUuid const &var) const
    {
        return QStringHash{}(var.toString());
    }
};

#endif //QT_TYPES_HASH_H
