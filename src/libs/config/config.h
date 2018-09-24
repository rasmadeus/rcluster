#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QVector>
#include <QUuid>
#include <storable.h>
#include "config_global.h"
#include "slave.h"

class CONFIG_SHARED_EXPORT Config : public QObject, public Storable
{
    Q_OBJECT

public:
    explicit Config(QObject *parent = nullptr);

public:
    QJsonObject toJson() const override;
    void fromJson(QJsonObject const &json) override;

public:
    QVector<QUuid> rootChildren() const { return children({}); }
    QVector<QUuid> children(QUuid const &id) const { return _children.value(id); }
    QVector<QUuid> descendants(QUuid const &id) const;
    QVector<QUuid> descendants(QUuid const &id, QString const &type) const;
    QVector<QUuid> slaves(QString const &type) const { return _types.value(type); }
    QList<QUuid> slaves() const { return _slaves.keys(); }
    Slave slave(QUuid const &id) const { return _slaves.value(id); }
    bool hasSlave(QUuid const &id) const { return _slaves.contains(id); }
    QVector<QUuid> localComputers() const;
    bool isLocal(QUuid const &id) const;
    QUuid parent(QUuid const &id, QString const &parentType) const;
    QUuid findLocalParam(QUuid const &id, QString const &key, QVariant const &param) const;
    QStringList types() const { return _types.keys(); }

public:
    void append(Slave const &slave);
    void remove(QUuid const &id);
    void enable(QUuid const &id);
    void disable(QUuid const &id);
    void rename(QUuid const &id, QString const &name);
    void update(QUuid const &id, QVariantHash const &params);
    void setProcessState(QUuid const &id, QProcess::ProcessState state);
    void setRuntimeParam(QUuid const &id, QString const &key, QVariant const &param);

signals:
    void reseted();
    void appended(QUuid const &id);
    void removed(QUuid const &id);
    void removeFinished(QUuid const &id);
    void enabled(QUuid const &id);
    void enableFinished(QUuid const &id);
    void disabled(QUuid const &id);
    void disableFinished(QUuid const &id);
    void renamed(QUuid const &id);
    void updated(QUuid const &id);
    void processStateChanged(QUuid const &id);
    void runtimeParamChanged(QUuid const &id, QString const &key);

private:
    bool appendSlave(Slave const &slave);
    void removeSlave(QUuid const &id);
    void enableFromTop(QUuid const &id);
    void enableToBottom(QUuid const &id);
    void disableFromBottom(QUuid const &id);

private:
    QHash<QUuid, Slave> _slaves;
    QHash<QUuid, QVector<QUuid>> _children;
    QHash<QString, QVector<QUuid>> _types;
};

#endif // CONFIG_H
