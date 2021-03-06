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
    MULTIMEDIA_LIBRARY

CONFIG += \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    multimedia_global.h \
    video_source_type.h \
    gloop.h \
    rtsp_server.h \
    camera_widget.h \
    gst_element_holder.h \
    gst_pipeline_observer.h \
    rtsp_renderer.h \
    video_writer.h
    pch.h

SOURCES += \
    video_source_type.cpp \
    gloop.cpp \
    rtsp_server.cpp \
    camera_widget.cpp \
    gst_element_holder.cpp \
    gst_pipeline_observer.cpp \
    rtsp_renderer.cpp \
    video_writer.cpp

DISTFILES += \
    multimedia.pro \
    multimedia.pri

TRANSLATIONS += \
    ../../translations/libs/multimedia_ru.ts \

include($$(PRO_ROOT)/src/common/common.pri)
include($$(PRO_ROOT)/src/common/gstreamer.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/utils/utils.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
