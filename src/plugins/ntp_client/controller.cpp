#include <QHostAddress>
#include <QHostInfo>
#include <QTimerEvent>
#include "controller.h"
#include "config.h"
#include "corebus.h"
#include "ntp_reply.h"

Controller::Controller(Config const &config, Plugin const &plugin, Corebus &corebus)
    : QObject{}
    , NodeController{ config, plugin, corebus }
    , _ntpClient{ *this }
{
    connect(&_ntpClient, &NtpClient::replyReceived, this, &Controller::onReply);
    connect(&_config, &Config::reseted, this, &Controller::restart);
}

void Controller::onSetup([[maybe_unused]] Node const &node)
{
    restart();
}

void Controller::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() == _timerId)
        sendRequest();
}

void Controller::onReply([[maybe_unused]] QHostAddress const &address, [[maybe_unused]] quint16 port, NtpReply const &reply)
{
    auto const offsetMs = reply.localClockOffset();

    if (correctLocalClock(offsetMs))
    {
        qDebug() << "System clock corrected with:" << offsetMs << "ms.";
        _corebus.send(QStringLiteral("SYSTEM_CLOCK_CORRECTED"), QStringLiteral("core"), { { QStringLiteral("offset"), offsetMs } });
    }
    else
    {
        qDebug() << "Failed to corrected system clock.";
        _corebus.send(QStringLiteral("FAILED_CORRECT_SYSTEM_CLOCK"), QStringLiteral("core"), { { QStringLiteral("offset"), offsetMs } });
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

    auto const node = _config.node(_corebus.id());
    _host = QHostInfo::fromName(node.param(QStringLiteral("host")).toString()).addresses().value(0);
    _port = static_cast<quint16>(node.param(QStringLiteral("port")).toInt());
    auto const seconds = node.param(QStringLiteral("sync_time_sec")).toInt();
    _syncTime = std::chrono::seconds{ seconds };
    _timerId = startTimer(seconds);

    sendRequest();
}
