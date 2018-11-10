TARGET = \
    camera

TEMPLATE = \
    lib

CONFIG += \
    precompile_header \
    warn_on \
    plugin \
    no_plugin_name_prefix

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    camera_editor.h \
    camera_plugin.h \
    camera_controller.h \
    web_camera_editor.h \
    display_editor.h

SOURCES += \
    camera_editor.cpp \
    camera_plugin.cpp \
    camera_controller.cpp \
    web_camera_editor.cpp \
    display_editor.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/camera_ru.ts \

include($$(PRO_ROOT)/src/common/common.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/libs/multimedia/multimedia.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
