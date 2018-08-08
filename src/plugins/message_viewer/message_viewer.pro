QT += \
    core \
    widgets

TARGET = \
    message_viewer

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
    message_viewer_editor.h \
    main_view.h \
    message_viewer_plugin.h

SOURCES += \
    message_viewer_editor.cpp \
    main_view.cpp \
    message_viewer_plugin.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/message_viewer_ru.ts \

include($$(PRO_ROOT)/src/common/globals.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
