#include <QDebug>
#include <QTcpSocket>
#include <message.h>
#include "client.h"

Client::Client(QTcpSocket &socket, QObject *parent)
    : QObject{ parent }
    , _corebus{ socket }
    , _messageController{ socket }
{
    connect(&_messageController, &MessageController::ready, this, &Client::ready);
    connect(&socket, &QTcpSocket::connected, this, &Client::connected);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::disconnected);
}

Client::~Client()
{
    if (_corebus.state() != QAbstractSocket::UnconnectedState)
    {
        _corebus.flush();
        _corebus.waitForBytesWritten();
    }
}
