#ifndef STORABLE_H
#define STORABLE_H

#include <QJsonObject>

class Storable
{
public:
    virtual ~Storable() = default;

public:
    virtual QJsonObject toJson() const = 0;
    virtual void fromJson(QJsonObject const &json) = 0;
};

#endif //STORABLE_H
