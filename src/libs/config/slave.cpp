#include <QJsonObject>
#include <QVariantHash>
#include "slave.h"

QJsonObject Slave::toJson() const
{
    return {
        { QStringLiteral("parent"), QJsonValue::fromVariant(_parent) },
        { QStringLiteral("type"), _type },
        { QStringLiteral("id"), QJsonValue::fromVariant(_id) },
        { QStringLiteral("name"), _name },
        { QStringLiteral("enabled"), _enabled },
        { QStringLiteral("params"), QJsonObject::fromVariantHash(_params) },
        { QStringLiteral("listeners"), _listeners.toArray() },
        { QStringLiteral("process_state"), _processState },
    };
}

void Slave::fromJson(QJsonObject const &json)
{
    _parent = json.value(QStringLiteral("parent")).toVariant().toUuid();
    _type = json.value(QStringLiteral("type")).toString();
    _id = json.value(QStringLiteral("id")).toVariant().toUuid();
    _name = json.value(QStringLiteral("name")).toString();
    _enabled = json.value(QStringLiteral("enabled")).toBool();
    _params = json.value(QStringLiteral("params")).toObject().toVariantHash();
    _listeners.fromArray(json.value(QStringLiteral("listeners")).toArray());
    _processState = json.value(QStringLiteral("process_state")).toVariant().value<QProcess::ProcessState>();
}
