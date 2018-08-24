#include <QUdpSocket>
#include <QHostAddress>
#include "ntp_client.h"
#include "ntp_packet.h"
#include "ntp_reply.h"
#include "ntp_reply_p.h"

NtpClient::NtpClient(QObject &parent)
    : QObject{ &parent }
{
    init(QHostAddress::Any, 0);
}

NtpClient::NtpClient(QHostAddress const &bindAddress, quint16 bindPort, QObject &parent)
    : QObject{ &parent }
{
    init(bindAddress, bindPort);
}

void NtpClient::init(QHostAddress const &bindAddress, quint16 bindPort)
{
    _corebus = new QUdpSocket{ this };
    _corebus->bind(bindAddress, bindPort);
    connect(_corebus, &QUdpSocket::readyRead, this, &NtpClient::readPendingDatagrams);
}

bool NtpClient::sendRequest(QHostAddress const &address, quint16 port)
{
    if(_corebus->state() != QAbstractSocket::BoundState)
        return false;

    NtpPacket packet;
    packet.flags.mode = ClientMode;
    packet.flags.versionNumber = 4;
    packet.transmitTimestamp = NtpTimestamp::fromDateTime(QDateTime::currentDateTimeUtc());

    auto const size = sizeof(packet);
    auto const sent = _corebus->writeDatagram(reinterpret_cast<char const *>(&packet), size, address, port);
    if (sent != size)
        qWarning() << "Socket last error:" << _corebus->errorString();

    return size == sent;
}

void NtpClient::readPendingDatagrams()
{
    while (_corebus->hasPendingDatagrams())
    {
        NtpFullPacket packet;

        QHostAddress address;
        quint16 port{ 0 };

        if(_corebus->readDatagram(reinterpret_cast<char*>(&packet), sizeof(packet), &address, &port) < static_cast<qint64>(sizeof(NtpPacket)))
            continue;

        auto const now = QDateTime::currentDateTime();

        auto replyPrivate = new NtpReplyPrivate();
        replyPrivate->packet = packet;
        replyPrivate->destinationTime = now;
        NtpReply reply{ replyPrivate };

        emit replyReceived(address, port, reply);
    }
}

