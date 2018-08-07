QT += \
    core \
    widgets \
    multimedia

TARGET = \
    display

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
    display_plugin.h

SOURCES += \
    display_plugin.cpp

RESOURCES += \
    $$PWD/res/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/display_ru.ts \

include($$(PRO_ROOT)/src/common/globals.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)