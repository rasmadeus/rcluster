#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <memory>
#include <QObject>
#include <QProcess>
#include <QUuid>
#include <plugin.h>

class Supervisor : public QObject
{
    Q_OBJECT

public:
    explicit Supervisor(Plugin* plugin, QUuid const &id, QString const &host, QString const &port, QObject &parent);
    ~Supervisor() override;

public:
    void start();

protected:
    void timerEvent(QTimerEvent *ev) override;

signals:
    void processStateChanged(QUuid const &id, QProcess::ProcessState state);

private:
    QString toString() const { return QStringLiteral("%1:%2").arg(_plugin->process()).arg(_id.toString()); }
    void stop();
    void restart(QProcess::ProcessState state);
    void processError(QProcess::ProcessError er);

private:
    QProcess *_process{ nullptr };
    Plugin* _plugin;
    QUuid const _id;
    QString const _host;
    QString const _port;
    int _restartTimer{ -1 };
};

#endif // SUPERVISOR_H
