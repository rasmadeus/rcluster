TARGET = \
    lab_rest_api

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
    lab_rest_api_controller.h \
    lab_rest_api_editor.h \
    lab_rest_api_plugin.h \
    access_point.h \
    lab_access_point.h

SOURCES += \
    lab_rest_api_controller.cpp \
    lab_rest_api_editor.cpp \
    lab_rest_api_plugin.cpp \
    access_point.cpp \
    lab_access_point.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/lab_rest_ru.ts \

include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/libs/multimedia/multimedia.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
