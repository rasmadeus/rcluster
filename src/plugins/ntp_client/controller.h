#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QHostAddress>
#include <QObject>
#include <slave_controller.h>
#include "ntp_client.h"

class Controller : public QObject, public SlaveController
{
    Q_OBJECT

public:
    explicit Controller(Config const &config, Plugin const &plugin, Corebus &corebus);

public:
    void onSetup(Slave const &slave) override;

protected:
    void timerEvent(QTimerEvent *ev) override;

private:
    void onReply(QHostAddress const &address, quint16 port, NtpReply const &reply);
    bool correctLocalClock(qint64 offsetMs);
    void sendRequest();
    void restart();

private:
    int _timerId{ -1 };
    NtpClient _ntpClient;
    QHostAddress _host;
    quint16 _port{ 0 };
    std::chrono::seconds _syncTime{ 0 };
};

#endif // CONTROLLER_H
