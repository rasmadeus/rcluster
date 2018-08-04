#include <QDebug>
#include <QTcpSocket>
#include <message.h>
#include "client.h"

Client::Client(QTcpSocket &socket, QObject *parent)
    : QObject{ parent }
    , _socket{ socket }
    , _messageController{ socket }
{
    connect(&_messageController, &MessageController::ready, this, &Client::ready);
    connect(&socket, &QTcpSocket::connected, this, &Client::connected);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::disconnected);
}

Client::~Client()
{
    if (_socket.state() != QAbstractSocket::UnconnectedState)
    {
        _socket.flush();
        _socket.waitForBytesWritten();
    }
}
