#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUuid>
#include <message_controller.h>

class QTcpSocket;

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QTcpSocket &socket, QObject *parent = nullptr);
    ~Client() override;

public:
    bool isEqual(QTcpSocket &socket) const { return &_corebus == &socket; }
    void send(Message const &message) { _messageController.send(message); }

    void setId(QUuid const &id) { _id = id; }
    QUuid const &id() const { return _id; }

signals:
    void ready(Message const &message);
    void connected();
    void disconnected();

private:
    QTcpSocket &_corebus;
    MessageController _messageController;
    QUuid _id;
};

#endif // CLIENT_H
