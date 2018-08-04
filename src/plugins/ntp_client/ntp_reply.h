#ifndef NTP_REPLY_H
#define NTP_REPLY_H

#include <QSharedDataPointer>
#include <QDateTime>
#include "ntp.h"

class NtpReplyPrivate;

class NtpReply
{
public:
    NtpReply();

public:
    NtpLeapIndicator leapIndicator() const;
    quint8 versionNumber() const;
    NtpMode mode() const;
    quint8 stratum() const;
    qreal pollInterval() const;
    qreal precision() const;
    QDateTime referenceTime() const;
    QDateTime originTime() const;
    QDateTime receiveTime() const;
    QDateTime transmitTime() const;
    QDateTime destinationTime() const;
    qint64 roundTripDelay() const;
    qint64 localClockOffset() const;
    bool isNull() const;

protected:
    friend class NtpClient;
    NtpReply(NtpReplyPrivate *dd);

private:
    QSharedDataPointer<NtpReplyPrivate> _d;
};


#endif // NTP_REPLY_H
