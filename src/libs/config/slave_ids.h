#ifndef SLAVE_IDS_H
#define SLAVE_IDS_H

#include <QJsonArray>
#include <QMetaType>
#include <QUuid>
#include <QSet>
#include "config_global.h"

class CONFIG_SHARED_EXPORT SlaveIds
{
public:
    SlaveIds() = default;
    SlaveIds(QJsonArray const &json);
    SlaveIds(QSet<QUuid> const &ids);

public:
    void append(QUuid const &id) { _ids << id; }
    bool remove(QUuid const &id) { return _ids.remove(id); }
    void clear() { _ids.clear(); }
    QSet<QUuid> const &ids() const { return _ids; }
    bool contains(QUuid const &id) const { return _ids.contains(id); }
    QJsonArray toArray() const;
    void fromArray(QJsonArray const &json);

private:
    QSet<QUuid> _ids;
};

#endif // SLAVE_IDS_H
