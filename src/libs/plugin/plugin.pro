TARGET = \
    plugin

TEMPLATE = \
    lib

DEFINES += \
    PLUGIN_LIBRARY

CONFIG += \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    plugin.h \
    plugin_global.h \
    default_base_plugin.h \
	device_controller.h \
    plugins.h \
    editor.h \
    default_base_editor.h \
    node_controller.h \
    controller_with_activity.h \
    controller_without_activity.h \
    editor_data.h
    pch.h

SOURCES += \
    plugin.cpp \
    default_base_plugin.cpp \
	device_controller.cpp \
    plugins.cpp \
    editor.cpp \
    default_base_editor.cpp \
    node_controller.cpp \
    controller_with_activity.cpp \
    controller_without_activity.cpp \
    editor_data.cpp

DISTFILES += \
    plugin.pri

TRANSLATIONS += \
    ../../translations/libs/plugin_ru.ts \

include($$(PRO_ROOT)/src/common/common.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
