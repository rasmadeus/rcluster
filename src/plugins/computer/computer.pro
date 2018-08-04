QT += \
    core \
    widgets \
    multimedia

TARGET = \
    computer

TEMPLATE = \
    lib

CONFIG += \
    c++14 \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    computer_editor.h \
    controller.h \
    computer_plugin.h

SOURCES += \
    computer_editor.cpp \
    controller.cpp \
    computer_plugin.cpp

RESOURCES += \
    $$PWD/res/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/computer_ru.ts \

include($$(PRO_ROOT)/src/common/globals.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
