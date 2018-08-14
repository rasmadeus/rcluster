QT += \
    core \
    widgets \
    network

TARGET = \
    camera

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
    camera_plugin.h

SOURCES += \
    camera_plugin.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/camera_ru.ts \

include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/transport/transport.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
