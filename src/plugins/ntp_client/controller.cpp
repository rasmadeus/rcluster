#include <QHostAddress>
#include <QHostInfo>
#include <QTimerEvent>
#include "controller.h"
#include "config.h"
#include "core_client_socket.h"
#include "ntp_reply.h"

Controller::Controller()
    : QObject{}
    , SlaveController{}
    , _ntpClient{ *this }
{
}

void Controller::init()
{
    connect(&_ntpClient, &NtpClient::replyReceived, this, &Controller::onReply);
    connect(_config, &Config::reseted, this, &Controller::restart);
    connect(_config, &Config::updated, this, &Controller::tryRestart);
}

void Controller::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() == _timerId)
        sendRequest();
}

void Controller::onReply(QHostAddress const &address, quint16 port, NtpReply const &reply)
{
    Q_UNUSED(address)
    Q_UNUSED(port)

    auto const offsetMs = reply.localClockOffset();

    if (correctLocalClock(offsetMs))
    {
        qDebug() << "System clock corrected with:" << offsetMs << "ms.";
        _socket->send(QStringLiteral("SYSTEM_CLOCK_CORRECTED"), QStringLiteral("core"), { { QStringLiteral("offset"), offsetMs } });
    }
    else
    {
        qDebug() << "Failed to corrected system clock.";
        _socket->send(QStringLiteral("FAILED_CORRECT_SYSTEM_CLOCK"), QStringLiteral("core"), { { QStringLiteral("offset"), offsetMs } });
    }
}

#ifdef Q_OS_WIN

#include <windows.h>

bool Controller::correctLocalClock(qint64 offsetMs)
{
    SYSTEMTIME now;
    GetSystemTime(&now);

    FILETIME buf;
    SystemTimeToFileTime(&now, &buf);

    ULONGLONG fileTimeBuf = ((static_cast<ULONGLONG>(buf.dwHighDateTime)) << 32) + buf.dwLowDateTime;
    fileTimeBuf += static_cast<unsigned long long>(offsetMs * (static_cast<qint64>(10000)));

    buf.dwLowDateTime  = static_cast<DWORD>((fileTimeBuf & 0xFFFFFFFF));
    buf.dwHighDateTime = static_cast<DWORD>((fileTimeBuf >> 32));

    qDebug() << "System time: " << now.wMilliseconds;

    FileTimeToSystemTime(&buf, &now);
    return SetSystemTime(&now) == TRUE;
}
#elif defined Q_OS_UNIX
bool Controller::correctLocalClock(qint64 offsetMs)
{
    return false;
}
#else
bool Controller::correctLocalClock(qint64 offsetMs)
{
    qDebug() << "Method didn't implement.";
    return false;
}
#endif

void Controller::sendRequest()
{
    auto const ok = _ntpClient.sendRequest(_host, _port);
    qDebug() << (ok ? "Request was sent succesfully." : "Failed to sent request.");
}

void Controller::restart()
{
    if (_timerId != -1)
        killTimer(_timerId);

    auto const slave = _config->slave(_socket->id());
    _host = QHostInfo::fromName(slave.param(QStringLiteral("host")).toString()).addresses().value(0);
    _port = static_cast<quint16>(slave.param(QStringLiteral("port")).toInt());
    _syncTime = std::chrono::seconds(slave.param(QStringLiteral("sync_time_sec")).toInt());
    _timerId = startTimer(_syncTime);

    sendRequest();
}

void Controller::tryRestart(QUuid const &id)
{
    if (id == _socket->id())
        restart();
}
