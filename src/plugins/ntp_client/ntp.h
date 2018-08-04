#ifndef NTP_H
#define NTP_H

enum NtpLeapIndicator
{
    NoWarning = 0,
    LastMinute61Warning = 1,
    LastMinute59Warning = 2,
    UnsynchronizedWarning = 3,
};

enum NtpMode
{
    ReservedMode = 0,
    SymmetricActiveMode = 1,
    SymmetricPassiveMode = 2,
    ClientMode = 3,
    ServerMode = 4,
    BroadcastMode = 5,
    ControlMode = 6,
    PrivateMode = 7,
};

enum NtpStratum
{
    UnspecifiedStratum = 0,
    PrimaryStratum = 1,
    SecondaryStratumFirst = 2,
    SecondaryStratumLast = 15,
    UnsynchronizedStratum = 16,
};

#endif // NTP_H
