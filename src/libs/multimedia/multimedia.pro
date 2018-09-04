QT  += \
    core \
    gui \
    widgets

TARGET = \
    multimedia

TEMPLATE = \
    lib

DEFINES += \
    MULTIMEDIA_LIBRARY

CONFIG += \
    c++14 \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    multimedia_global.h \
    rtsp_server.h \
    gloop.h
    pch.h

SOURCES += \
    rtsp_server.cpp \
    gloop.cpp

DISTFILES += \
    multimedia.pri

TRANSLATIONS += \
    ../../translations/libs/multimedia_ru.ts \

include($$(PRO_ROOT)/src/common/gstreamer.pri)
include($$(PRO_ROOT)/src/libs/utils/utils.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
