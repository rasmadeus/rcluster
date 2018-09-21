TARGET = \
    media_player

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
    media_player_controller.h \
    media_player_editor.h \
    media_player_plugin.h \
    files_model.h

SOURCES += \
    media_player_controller.cpp \
    media_player_editor.cpp \
    media_player_plugin.cpp \
    files_model.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/media_player_ru.ts \

include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/libs/multimedia/multimedia.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
