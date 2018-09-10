#ifndef PCH_H
#define PCH_H

extern "C"
{
    #include <libavdevice/avdevice.h>
    #include <libavformat/avformat.h>
}

#if defined __cplusplus
    #include <QtCore>
    #include <QtGui>
    #include <QtWidgets>
#endif

#endif // PCH_H
