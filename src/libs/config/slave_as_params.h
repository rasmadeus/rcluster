#ifndef SLAVE_AS_PARAMS_H
#define SLAVE_AS_PARAMS_H

#include <QHash>
#include <QUuid>
#include <QSet>
#include <storable.h>
#include "config_global.h"

class CONFIG_SHARED_EXPORT SlaveAsParams : public Storable
{
public:
    SlaveAsParams() = default;
    SlaveAsParams(QJsonObject const &json);
    SlaveAsParams(QString const &key, QSet<QUuid> const &slaves);

public:
    QJsonObject toJson() const override;
    void fromJson(QJsonObject const &json) override;

public:
    void setSlaves(QString const &key, QSet<QUuid> const &slaves) { _params[key] = slaves; }
    void append(QString const &key, QUuid const &slave) { _params[key] << slave; }
    bool remove(QUuid const &slave);
    QStringList keys() const { return _params.keys(); }
    QSet<QUuid> slaves(QString const &key) const { return _params.value(key); }
    bool contains(QUuid const &id) const;

private:
    QHash<QString, QSet<QUuid>> _params;
};

#endif // SLAVE_AS_PARAMS_H
