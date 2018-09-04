QT  += \
    core \
    gui \
    widgets \
    multimedia

TARGET = \
    multimedia

TEMPLATE = \
    lib

DEFINES += \
    MULTIMEDIA_LIBRARY \
    __STDC_CONSTANT_MACROS

CONFIG += \
    c++14 \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    multimedia_global.h \
    video_source.h
    pch.h

SOURCES += \
    video_source.cpp

DISTFILES += \
    multimedia.pri

TRANSLATIONS += \
    ../../translations/libs/multimedia_ru.ts \

include($$(PRO_ROOT)/src/common/ffmpeg.pri)
include($$(PRO_ROOT)/src/libs/utils/utils.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
