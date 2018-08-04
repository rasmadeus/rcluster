#ifndef NTP_REPLY_P_H
#define NTP_REPLY_P_H

#include <QSharedData>
#include "ntp_packet.h"

class NtpReplyPrivate: public QSharedData
{
public:
    NtpFullPacket packet;
    QDateTime destinationTime;
};

#endif // NTP_REPLY_P_H
