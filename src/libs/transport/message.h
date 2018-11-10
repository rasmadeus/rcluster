#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDateTime>
#include <QVariantHash>
#include <QUuid>
#include <storable.h>
#include "transport_global.h"

class TRANSPORT_SHARED_EXPORT Message : public Storable
{
public:
    Message() = default;
    Message(QString const &action, QString const &to, QString const &from, QVariantHash const &params);

public:
    QJsonObject toJson() const override;
    void fromJson(QJsonObject const &json) override;

public:
    QDateTime const &createDateTime() const { return _createDateTime; }
    QString const &action() const { return _action; }
    QString const &to() const { return _to; }
    QUuid toId() const { return QUuid::fromString(_to); }
    QUuid fromId() const { return QUuid::fromString(_from); }
    QString const &from() const { return _from; }
    QVariant param(QString const &key) const { return _params.value(key); }
    QString toString() const;
    QVariantHash const &params() const { return _params; }

private:
    QDateTime _createDateTime{ QDateTime::currentDateTimeUtc() };
    QString _action;
    QString _to;
    QString _from;
    QVariantHash _params;
};

Q_DECLARE_METATYPE(Message)

#endif // MESSAGE_H
