#ifndef SLAVE_H
#define SLAVE_H

#include <QVariantHash>
#include <storable.h>
#include <slave_ids.h>

class CONFIG_SHARED_EXPORT Slave : public Storable
{
public:
    QJsonObject toJson() const override;
    void fromJson(QJsonObject const &json) override;

public:
    QUuid const &parent() const { return _parent; }
    void setParent(QUuid const &parent) { _parent = parent; }

    QUuid const &id() const { return _id; }
    void setId(QUuid const &id) { _id = id; }

    QString const &type() const { return _type; }
    void setType(QString const &type) { _type = type; }

    QString const &name() const { return _name; }
    void setName(QString const &name) { _name = name; }

    bool enabled() const { return _enabled; }
    bool disabled() const { return !_enabled; }
    void enable() { _enabled = true; }
    void disable() { _enabled = false; }

    QVariantHash const &params() const { return _params; }
    QVariant param(QString const &key) const { return _params.value(key); }
    void update(QVariantHash const &params) { _params = params; }

    void setListeners(SlaveIds const &listeners) { _listeners = listeners; }
    void appendListener(QUuid const &id) { return _listeners.append(id); }
    bool removeListener(QUuid const &id) { return _listeners.remove(id); }
    bool isListener(QUuid const &id) const { return _listeners.contains(id); }
    SlaveIds const &listeners() const { return _listeners; }

private:
    QUuid _parent;
    QString _type{ "ROOT" };
    QUuid _id;
    QString _name;
    bool _enabled{ true };
    QVariantHash _params;
    SlaveIds _listeners;
};

#endif // SLAVE_H
