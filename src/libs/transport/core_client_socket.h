#ifndef CORE_CLIENT_SOCKET_H
#define CORE_CLIENT_SOCKET_H

#include <QTcpSocket>
#include <QUuid>
#include <globals.h>
#include <message_controller.h>
#include <transport_global.h>

class QTcpSocket;

class TRANSPORT_SHARED_EXPORT CoreClientSocket : public QObject
{
    Q_OBJECT

public:
    explicit CoreClientSocket(QUuid const &id, QObject *parent = nullptr);
    ~CoreClientSocket() override;

public:
    QUuid const &id() const { return _id; }

    void connectToHost(QString const &host, quint16 port = rcluster::corePort());
    void disconnectFromHost();

    QAbstractSocket::SocketState state() const { return _socket.state(); }
    QString const &host() const { return _host; }
    quint16 port() const { return _port; }

    void send(QString const &action, QString const &to = QStringLiteral("core"), QVariantHash const &params = {});

signals:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState state);
    void ready(Message const &message);

protected:
    void timerEvent(QTimerEvent *ev) override;

private:
    void connectToHost();
    void start();
    void stop();

private:
    QUuid _id;
    QTcpSocket _socket;
    MessageController _messageController;
    QString _host;
    quint16 _port{ rcluster::corePort() };
    int _timerId{ -1 };
    bool _autoConnect{ true };
};

#endif // CORE_CLIENT_SOCKET_H
