TARGET = \
    experiment_center

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
    experiment_center_controller.h \
    experiment_center_editor.h \
    experiment_center_plugin.h \
    experiment_actions.h \
    experiment_center.h \
    devices_view.h \
    devices_model.h \
    device_record.h

SOURCES += \
    experiment_center_controller.cpp \
    experiment_center_editor.cpp \
    experiment_center_plugin.cpp \
    experiment_actions.cpp \
    experiment_center.cpp \
    devices_view.cpp \
    devices_model.cpp \
    device_record.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/experiment_center_ru.ts \

include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
