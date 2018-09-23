#include <chrono>
#include <QSettings>
#include <QTcpSocket>
#include <QTimerEvent>
#include "corebus.h"
#include "message.h"

Corebus::Corebus(const QUuid &id, QObject *parent)
    : QObject{ parent }
    , _id{ id }
    , _messageController{ _corebus }
{
    connect(&_corebus, &QTcpSocket::connected, this, &Corebus::stop);
    connect(&_corebus, &QTcpSocket::disconnected, this, &Corebus::start);
    connect(&_corebus, &QTcpSocket::stateChanged, this, &Corebus::stateChanged);
    connect(&_messageController, &MessageController::ready, this, &Corebus::ready);
}

Corebus::~Corebus()
{
    if (_corebus.state() != QAbstractSocket::UnconnectedState)
    {
        _corebus.flush();
        _corebus.waitForBytesWritten();
        disconnectFromHost();

        if (_corebus.state() != QAbstractSocket::UnconnectedState)
            _corebus.waitForDisconnected();
    }
}

void Corebus::connectToHost(QString const &host, quint16 port)
{
    _host = host;
    _port = port;
    _autoConnect = true;

    if (_corebus.state() != QAbstractSocket::UnconnectedState)
    {
        _corebus.disconnectFromHost();
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

void Corebus::disconnectFromHost()
{
    _autoConnect = false;

    if (_corebus.state() != QAbstractSocket::UnconnectedState)
        _corebus.disconnectFromHost();
}

void Corebus::send(const QString &action, const QString &to, const QVariantHash &params)
{
    _messageController.send({ action, to, _id.toString(), params });
}

void Corebus::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() == _timerId)
        connectToHost();
}

void Corebus::connectToHost()
{
    if (_corebus.state() == QAbstractSocket::UnconnectedState)
        _corebus.connectToHost(_host, _port);
}

void Corebus::start()
{
    emit disconnected();
    Q_ASSERT(_timerId == -1);

    if (_autoConnect)
        _timerId = startTimer(std::chrono::seconds(5));
}

void Corebus::stop()
{
    send(QStringLiteral("REGISTER"));
    emit connected();
    Q_ASSERT(_timerId != -1);
    killTimer(_timerId);
    _timerId = -1;
}
