#ifndef VIDEO_SOURCE_TYPE_H
#define VIDEO_SOURCE_TYPE_H

#include <QMetaType>
#include "multimedia_global.h"

enum class MULTIMEDIA_SHARED_EXPORT VideoSourceType
{
    Fake,
    WebCamera,
};

Q_DECLARE_METATYPE(VideoSourceType)

#endif // VIDEO_SOURCE_TYPE_H
