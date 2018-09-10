#ifndef PCH_H
#define PCH_H

extern "C"
{
    #include <gst/gst.h>
    #include <gst/rtsp-server/rtsp-server.h>
}

#if defined __cplusplus
    #include <QtCore>
#endif

#endif // PCH_H
