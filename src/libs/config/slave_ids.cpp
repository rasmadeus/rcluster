#include <QVariant>
#include "slave_ids.h"

SlaveIds::SlaveIds(QJsonArray const &json)
{
    fromArray(json);
}

SlaveIds::SlaveIds(QSet<QUuid> const &ids)
    : _ids{ ids }
{
}

QJsonArray SlaveIds::toArray() const
{
    QJsonArray json;
    for(auto const &id : _ids)
        json << QJsonValue::fromVariant(id);
    return json;
}

void SlaveIds::fromArray(QJsonArray const &json)
{
    clear();

    for(auto const &value : json)
        _ids << value.toVariant().toUuid();
}
