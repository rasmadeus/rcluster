TARGET = \
    message_viewer

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
    message_viewer_editor.h \
    message_viewer_plugin.h \
    message_viewer_controller.h

SOURCES += \
    message_viewer_editor.cpp \
    message_viewer_plugin.cpp \
    message_viewer_controller.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/message_viewer_ru.ts \

include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
