#ifndef SLAVE_H
#define SLAVE_H

#include <QProcess>
#include <QVariantHash>
#include <storable.h>
#include "config_global.h"

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
    void setParams(QVariantHash const &params) { _params = params; }
    void setParams(QVariantHash &&params) { _params = std::move(params); }

    QProcess::ProcessState processState() const { return _processState; }
    void setProcessState(QProcess::ProcessState state) { _processState = state; }

    void setRuntimeParam(QString const &key, QVariant const &value) { _runtimeParams[key] = value; }
    QVariant runtimeParam(QString const &key) const { return _runtimeParams.value(key); }

    bool isFake() const { return _params.value(QStringLiteral("is_fake")).toBool(); }

private:
    QUuid _parent;
    QString _type{ "ROOT" };
    QUuid _id;
    QString _name;
    bool _enabled{ true };
    QVariantHash _params;
    QProcess::ProcessState _processState{ QProcess::NotRunning };
    QVariantHash _runtimeParams;
};

#endif // SLAVE_H
