#ifndef CAMERA_H
#define CAMERA_H

extern "C"
{
    #include <libavdevice/avdevice.h>
    #include <libswscale/swscale.h>
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
}


#include <QObject>

class Camera : public QObject
{
    Q_OBJECT

public:
    explicit Camera(QString const &deviceName);
};

#endif // CAMERA_H
