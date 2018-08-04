#include <QJsonDocument>
#include <QTcpSocket>
#include "message.h"
#include "message_controller.h"

MessageController::MessageController(QTcpSocket &socket, QObject *parent)
    : QObject{ parent }
    , _socket{ socket }
    , _in{ &_socket }
    , _out{ &_socket }
{
    connect(&_socket, &QTcpSocket::readyRead, this, &MessageController::receive);
    connect(&_socket, &QTcpSocket::disconnected, this, &MessageController::reset);
}

void MessageController::send(Message const &message)
{
    if (_socket.state() != QAbstractSocket::ConnectedState)
    {
        qCritical() << "Failed to send message due to unconnected socket.";
        return;
    }

    auto const data = QJsonDocument{ message.toJson() }.toJson(QJsonDocument::Compact);
    qDebug() << "Message to send:" << data;

    _out << data.size();
    _out << data;
}

void MessageController::receive()
{
    switch(_state)
    {
        case State::WaitMessageSize: receiveMessageSize(); break;
        case State::WaitMessageData: receiveMessageBody(); break;
    }
}

void MessageController::receiveMessageSize()
{
    if (_socket.bytesAvailable() >= static_cast<qint64>(sizeof(decltype(_msgSize))))
    {
        readMessageSize();
        continueProcessing();
    }
}

void MessageController::receiveMessageBody()
{
    if (_socket.bytesAvailable() >= _msgSize)
    {
        readMessageBody();
        reset();
        continueProcessing();
    }
}

void MessageController::readMessageSize()
{
    _in >> _msgSize;
    _state = State::WaitMessageData;
}

void MessageController::readMessageBody()
{
    QByteArray data;
    _in >> data;

    Message msg;
    msg.fromJson(QJsonDocument::fromJson(data).object());
    qDebug() << "Message received:" << msg.toJson();
    emit ready(msg);
}

void MessageController::reset()
{
    _state = State::WaitMessageSize;
    _msgSize = 0;
}

void MessageController::continueProcessing()
{
    if (_socket.bytesAvailable() > 0)
        receive();
}
