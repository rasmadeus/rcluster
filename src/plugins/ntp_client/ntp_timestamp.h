#ifndef NTP_TIMESTAMP_H
#define NTP_TIMESTAMP_H

#include <QtGlobal>
#include <QtEndian>
#include <QDateTime>

namespace detail
{
    namespace
    {
        qint64 const january_1_1900 = -2208988800000ll;
    }
}

struct NtpTimestamp
{
    quint32 seconds{ 0 };
    quint32 fraction{ 0 };

    static NtpTimestamp fromDateTime(QDateTime const &dateTime)
    {
        qint64 const ntpMSecs = dateTime.toMSecsSinceEpoch() - detail::january_1_1900;
        quint32 const seconds = static_cast<quint32>(ntpMSecs / 1000);
        quint32 const fraction = 0x100000000ll * (ntpMSecs % 1000) / 1000;

        NtpTimestamp result;
        result.seconds = qToBigEndian(seconds);
        result.fraction = qToBigEndian(fraction);
        return result;
    }

    static QDateTime toDateTime(NtpTimestamp const &ntpTime)
    {
        quint32 const seconds = qFromBigEndian(ntpTime.seconds);
        quint32 const fraction = qFromBigEndian(ntpTime.fraction);
        qint64 const ntpMSecs = seconds * 1000ll + fraction * 1000ll / 0x100000000ll;
        return QDateTime::fromMSecsSinceEpoch(ntpMSecs + detail::january_1_1900);
    }
};

#endif // NTP_TIMESTAMP_H
