#ifndef PCH_H
#define PCH_H

extern "C"
{
    #include <gst/gst.h>
    #include <gst/rtsp-server/rtsp-server.h>
}

#if defined __cplusplus
    #include <unordered_map>
    #include <QtCore>
    #include <QtGui>
    #include <QtWidgets>
#endif

#endif // PCH_H
