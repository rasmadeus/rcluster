TARGET = \
    respondent_place

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
    respondent_place_editor.h \
    respondent_place_plugin.h \
    device_model.h

SOURCES += \
    respondent_place_editor.cpp \
    respondent_place_plugin.cpp \
    device_model.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/respondent_place_ru.ts \

include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
