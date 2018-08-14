#ifndef NTP_CLIENT_H
#define NTP_CLIENT_H

#include <QObject>
#include "ntp.h"

class QUdpSocket;
class QHostAddress;
class NtpReply;

class NtpClient: public QObject
{
    Q_OBJECT

public:
    explicit NtpClient(QObject &parent);
    explicit NtpClient(QHostAddress const &bindAddress, quint16 bindPort, QObject &parent);

public:
    bool sendRequest(QHostAddress const &address, quint16 port);

signals:
    void replyReceived(QHostAddress const &address, quint16 port, NtpReply const &reply);

private:
    void readPendingDatagrams();
    void init(QHostAddress const &bindAddress, quint16 bindPort);

private:
    QUdpSocket *_corebus;
};

#endif // NTP_CLIENT_H
