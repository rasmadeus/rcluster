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
    rtsp_server.h \
    rtsp_server_runner.h \
    fake_camera_controller.h \
    fake_camera_editor.h \
    fake_camera_plugin.h

SOURCES += \
    rtsp_server.cpp \
    rtsp_server_runner.cpp \
    fake_camera_controller.cpp \
    fake_camera_editor.cpp \
    fake_camera_plugin.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/web_camera_ru.ts \

include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/gstreamer.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
