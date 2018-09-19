#ifndef VIDEO_SOURCE_TYPE_H
#define VIDEO_SOURCE_TYPE_H

#include <QMetaType>

enum class VideoSourceType
{
    FakeCamera,
    WebCamera,
    Display,
};

Q_DECLARE_METATYPE(VideoSourceType)

#endif // VIDEO_SOURCE_TYPE_H
