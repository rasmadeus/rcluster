#ifndef RTSPCLIENT_H
#define RTSPCLIENT_H

#include <QWidget>
#include "multimedia_global.h"

class MULTIMEDIA_SHARED_EXPORT RtspClient
{
public:
    RtspClient(QString const &url, WId id);
    ~RtspClient();
};

#endif // RTSPCLIENT_H
