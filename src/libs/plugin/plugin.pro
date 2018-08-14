TARGET = \
    plugin

TEMPLATE = \
    lib

DEFINES += \
    PLUGIN_LIBRARY

CONFIG += \
    c++11 \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    plugin.h \
    plugin_global.h \
    default_base_plugin.h \
    plugins.h \
    editor.h \
    default_base_editor.h \
    slave_controller.h \
    main_view_controller.h
    pch.h

SOURCES += \
    plugin.cpp \
    default_base_plugin.cpp \
    plugins.cpp \
    editor.cpp \
    default_base_editor.cpp \
    slave_controller.cpp \
    main_view_controller.cpp

DISTFILES += \
    plugin.pri

TRANSLATIONS += \
    ../../translations/libs/plugin_ru.ts \

include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
