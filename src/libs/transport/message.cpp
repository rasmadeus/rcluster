#include <QJsonDocument>
#include <QJsonObject>
#include "message.h"

Message::Message(QString const &action, const QString &to, const QString &from, QVariantHash const &params)
    : _action{ action }
    , _to{ to }
    , _from{ from }
    , _params{ params }
{
}

QJsonObject Message::toJson() const
{
    return {
        { QStringLiteral("action"), _action },
        { QStringLiteral("to"), _to },
        { QStringLiteral("from"), _from },
        { QStringLiteral("params"), QJsonObject::fromVariantHash(_params) },
        { QStringLiteral("create_date_time_utc"), _createDateTime.toString(Qt::ISODateWithMs) },
    };
}

void Message::fromJson(QJsonObject const &json)
{
    _action = json.value(QStringLiteral("action")).toString();
    _to = json.value(QStringLiteral("to")).toString();
    _from = json.value(QStringLiteral("from")).toString();
    _params = json.value(QStringLiteral("params")).toObject().toVariantHash();
    _createDateTime = QDateTime::fromString(json.value(QStringLiteral("create_date_time_utc")).toString(), Qt::ISODateWithMs);
}

QString Message::toString() const
{
    return QJsonDocument{ toJson() }.toJson();
}
