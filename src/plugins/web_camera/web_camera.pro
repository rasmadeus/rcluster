QT += \
    core \
    widgets \
    network

TARGET = \
    web_camera

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
    web_camera_editor.h \
    main_view.h \
    web_camera_plugin.h

SOURCES += \
    web_camera_editor.cpp \
    main_view.cpp \
    web_camera_plugin.cpp

RESOURCES += \
    $$PWD/res/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/web_camera_ru.ts \

include($$(PRO_ROOT)/src/common/globals.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/transport/transport.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
