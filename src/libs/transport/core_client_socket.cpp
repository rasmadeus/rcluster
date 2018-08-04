#include <chrono>
#include <QSettings>
#include <QTcpSocket>
#include <QTimerEvent>
#include "core_client_socket.h"
#include "message.h"

CoreClientSocket::CoreClientSocket(const QUuid &id, QObject *parent)
    : QObject{ parent }
    , _id{ id }
    , _messageController{ _socket }
{
    connect(&_socket, &QTcpSocket::connected, this, &CoreClientSocket::stop);
    connect(&_socket, &QTcpSocket::disconnected, this, &CoreClientSocket::start);
    connect(&_socket, &QTcpSocket::stateChanged, this, &CoreClientSocket::stateChanged);
    connect(&_messageController, &MessageController::ready, this, &CoreClientSocket::ready);
}

CoreClientSocket::~CoreClientSocket()
{
    if (_socket.state() != QAbstractSocket::UnconnectedState)
    {
        _socket.flush();
        _socket.waitForBytesWritten();
        disconnectFromHost();

        if (_socket.state() != QAbstractSocket::UnconnectedState)
            _socket.waitForDisconnected();
    }
}

void CoreClientSocket::connectToHost(QString const &host, quint16 port)
{
    _host = host;
    _port = port;
    _autoConnect = true;

    if (_socket.state() != QAbstractSocket::UnconnectedState)
    {
        _socket.disconnectFromHost();
    }
    else
    {
        if (_timerId == -1)
        {
            start();
            connectToHost();
        }
    }
}

void CoreClientSocket::disconnectFromHost()
{
    _autoConnect = false;

    if (_socket.state() != QAbstractSocket::UnconnectedState)
        _socket.disconnectFromHost();
}

void CoreClientSocket::send(const QString &action, const QString &to, const QVariantHash &params)
{
    _messageController.send({ action, to, _id.toString(), params });
}

void CoreClientSocket::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() == _timerId)
        connectToHost();
}

void CoreClientSocket::connectToHost()
{
    if (_socket.state() == QAbstractSocket::UnconnectedState)
        _socket.connectToHost(_host, _port);
}

void CoreClientSocket::start()
{
    emit disconnected();
    Q_ASSERT(_timerId == -1);

    if (_autoConnect)
        _timerId = startTimer(std::chrono::seconds(5));
}

void CoreClientSocket::stop()
{
    send(QStringLiteral("REGISTER"));
    emit connected();
    Q_ASSERT(_timerId != -1);
    killTimer(_timerId);
    _timerId = -1;
}
