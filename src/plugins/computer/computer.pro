QT += \
    multimedia

TARGET = \
    computer

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
    computer_editor.h \
    computer_plugin.h \
    computer_controller.h

SOURCES += \
    computer_editor.cpp \
    computer_plugin.cpp \
    computer_controller.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/computer_ru.ts \

include($$(PRO_ROOT)/src/common/common.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
