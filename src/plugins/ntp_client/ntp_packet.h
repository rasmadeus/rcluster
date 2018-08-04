#ifndef NTP_PACKET_H
#define NTP_PACKET_H

#include <QtGlobal>
#include "ntp.h"
#include "ntp_timestamp.h"

struct NtpPacketFlags
{
    unsigned char mode: 3;
    unsigned char versionNumber: 3;
    unsigned char leapIndicator: 2;
};

struct NtpPacket
{
    NtpPacketFlags flags{ 0, 0, 0 };
    quint8 stratum{ 0 };
    qint8 poll{ 0 };
    qint8 precision{ 0 };
    qint32 rootDelay{ 0 };
    qint32 rootDispersion{ 0 };
    qint8 referenceID[4] = { 0, 0, 0, 0 };
    NtpTimestamp referenceTimestamp;
    NtpTimestamp originateTimestamp;
    NtpTimestamp receiveTimestamp;
    NtpTimestamp transmitTimestamp;
};

struct NtpAuthenticationInfo
{
    quint32 keyId{ 0 };
    quint8 messageDigest[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};

struct NtpFullPacket
{
    NtpPacket basic;
    NtpAuthenticationInfo auth;
};

#endif // NTP_PACKET_H
