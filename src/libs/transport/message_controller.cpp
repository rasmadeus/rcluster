#include <QJsonDocument>
#include <QTcpSocket>
#include "message.h"
#include "message_controller.h"

MessageController::MessageController(QTcpSocket &socket, QObject *parent)
    : QObject{ parent }
    , _corebus{ socket }
    , _in{ &_corebus }
    , _out{ &_corebus }
{
    connect(&_corebus, &QTcpSocket::readyRead, this, &MessageController::receive);
    connect(&_corebus, &QTcpSocket::disconnected, this, &MessageController::reset);
}

void MessageController::send(Message const &message)
{
    if (_corebus.state() != QAbstractSocket::ConnectedState)
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
    if (_corebus.bytesAvailable() >= static_cast<qint64>(sizeof(decltype(_msgSize))))
    {
        readMessageSize();
        continueProcessing();
    }
}

void MessageController::receiveMessageBody()
{
    if (_corebus.bytesAvailable() >= _msgSize)
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
    if (_corebus.bytesAvailable() > 0)
        receive();
}
