TARGET = \
    respondent_places

TEMPLATE = \
    lib

CONFIG += \
    c++14 \
    precompile_header \
    warn_on \
    plugin \
    no_plugin_name_prefix

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    respondent_places_plugin.h

SOURCES += \
    respondent_places_plugin.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/respondent_places_ru.ts \

include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
