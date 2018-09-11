TARGET = \
    experiment_center

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
    experiment_center_controller.h \
    experiment_center_editor.h \
    experiment_center_plugin.h

SOURCES += \
    experiment_center_controller.cpp \
    experiment_center_editor.cpp \
    experiment_center_plugin.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/experiment_center_ru.ts \

include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/libs/multimedia/multimedia.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
