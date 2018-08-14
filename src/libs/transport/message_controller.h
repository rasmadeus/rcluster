#ifndef MESSAGE_RECEIVER_H
#define MESSAGE_RECEIVER_H

#include <QDataStream>
#include <QObject>

#include "transport_global.h"

class Message;
class Event;
class QTcpSocket;
class Storable;

class TRANSPORT_SHARED_EXPORT MessageController : public QObject
{
    Q_OBJECT

public:
    explicit MessageController(QTcpSocket &socket, QObject *parent = nullptr);

public:
    void send(Message const &message);

signals:
    void ready(Message const &message);

private:
    void receive();
    void receiveMessageSize();
    void receiveMessageBody();
    void readMessageSize();
    void readMessageBody();
    void reset();
    void continueProcessing();

private:
    enum class State
    {
        WaitMessageSize,
        WaitMessageData,
    };

private:
    QTcpSocket &_corebus;
    QDataStream _in;
    State _state{ State::WaitMessageSize };
    int _msgSize{ 0 };
    QDataStream _out;
};

#endif // MESSAGE_RECEIVER_H
