TARGET = \
    template

TEMPLATE = \
    lib

CONFIG += \
    precompile_header \
    warn_on \
    plugin

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    template_controller.h \
    template_plugin.h \
    template_editor.h

SOURCES += \
    template_controller.cpp \
    template_editor.cpp \
    template_plugin.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/template_ru.ts \

include($$(PRO_ROOT)/src/common/common.pri)	
include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/libs/multimedia/multimedia.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
