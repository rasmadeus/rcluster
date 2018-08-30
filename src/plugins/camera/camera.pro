TARGET = \
    camera

TEMPLATE = \
    lib

CONFIG += \
    c++14 \
    precompile_header \
    warn_on \
    plugin

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    camera_editor.h \
    camera_plugin.h \
    camera_controller.h \
    rtsp_server.h \
    rtsp_server_runner.h

SOURCES += \
    camera_editor.cpp \
    camera_plugin.cpp \
    camera_controller.cpp \
    rtsp_server.cpp \
    rtsp_server_runner.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/camera_ru.ts \

include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/gstreamer.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
