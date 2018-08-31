#include <QJsonArray>
#include <QVariant>
#include "slave_as_params.h"

SlaveAsParams::SlaveAsParams(QJsonObject const &json)
{
    fromJson(json);
}

SlaveAsParams::SlaveAsParams(QString const &key, QSet<QUuid> const &slaves)
{
    setSlaves(key, slaves);
}

QJsonObject SlaveAsParams::toJson() const
{
    QJsonObject res;
    for(auto const &key : keys())
    {
        QJsonArray ids;
        for(auto const &id : _params[key])
            ids << QJsonValue::fromVariant(id);
        res[key] = std::move(ids);
    }
    return res;
}

void SlaveAsParams::fromJson(QJsonObject const &json)
{
    _params.clear();

    for(auto const &key : json.keys())
    {
        QSet<QUuid> ids;
        for(auto id : json.value(key).toArray())
            ids << id.toVariant().toUuid();
        _params[key] = std::move(ids);
    }
}

bool SlaveAsParams::remove(QUuid const &slave)
{
    bool ok = false;
    for(auto const &key : keys())
    {
        if ( _params[key].remove(slave))
        {
            ok = true;
            if (_params[key].isEmpty())
                _params.remove(key);
        }
    }
    return ok;
}

bool SlaveAsParams::contains(QUuid const &id) const
{
    return std::any_of(_params.cbegin(), _params.cend(), [&id](auto const &ids){ return ids.contains(id); });
}
