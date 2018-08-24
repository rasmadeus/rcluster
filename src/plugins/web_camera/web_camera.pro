TARGET = \
    web_camera

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
    web_camera_editor.h \
    web_camera_plugin.h \
    controller.h

SOURCES += \
    web_camera_editor.cpp \
    web_camera_plugin.cpp \
    controller.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/web_camera_ru.ts \

include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
