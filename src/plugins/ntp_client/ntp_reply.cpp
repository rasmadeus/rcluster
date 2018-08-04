#include <cmath>
#include "ntp_reply.h"
#include "ntp_reply_p.h"

NtpReply::NtpReply()
    : _d{ new NtpReplyPrivate{} }
{
}

NtpReply::NtpReply(NtpReplyPrivate *dd)
    : _d{ dd }
{
}

NtpLeapIndicator NtpReply::leapIndicator() const
{
    return static_cast<NtpLeapIndicator>(_d->packet.basic.flags.leapIndicator);
}

quint8 NtpReply::versionNumber() const
{
    return _d->packet.basic.flags.versionNumber;
}

NtpMode NtpReply::mode() const
{
    return static_cast<NtpMode>(_d->packet.basic.flags.mode);
}

quint8 NtpReply::stratum() const
{
    return _d->packet.basic.stratum;
}

qreal NtpReply::pollInterval() const
{
    return std::pow(static_cast<qreal>(2), static_cast<qreal>(_d->packet.basic.poll));
}

qreal NtpReply::precision() const
{
    return std::pow(static_cast<qreal>(2), static_cast<qreal>(_d->packet.basic.precision));
}

QDateTime NtpReply::referenceTime() const
{
    return NtpTimestamp::toDateTime(_d->packet.basic.referenceTimestamp);
}

QDateTime NtpReply::originTime() const
{
    return NtpTimestamp::toDateTime(_d->packet.basic.originateTimestamp);
}

QDateTime NtpReply::receiveTime() const
{
    return NtpTimestamp::toDateTime(_d->packet.basic.receiveTimestamp);
}

QDateTime NtpReply::transmitTime() const
{
    return NtpTimestamp::toDateTime(_d->packet.basic.transmitTimestamp);
}

QDateTime NtpReply::destinationTime() const
{
    return _d->destinationTime;
}

qint64 NtpReply::roundTripDelay() const
{
    return originTime().msecsTo(destinationTime()) - receiveTime().msecsTo(transmitTime());
}

qint64 NtpReply::localClockOffset() const
{
   return (originTime().msecsTo(receiveTime()) + destinationTime().msecsTo(transmitTime())) / 2;
}

bool NtpReply::isNull() const
{
    return _d->destinationTime.isNull();
}
