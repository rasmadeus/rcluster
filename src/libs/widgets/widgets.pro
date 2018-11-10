TARGET = \
    widgets

TEMPLATE = \
    lib

DEFINES += \
    WIDGETS_LIBRARY

CONFIG += \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    widgets_global.h \
    node_item.h \
    node_model.h \
    node_sort_model.h \
    actions.h \
    port_spin_box.h \
    data_combo_box.h \
    device_proxy_model.h \
    node_type_proxy_model.h \
    node_check_model.h \
    node_item_model.h \
    pass_line_edit.h \
    splash_screen.h \
    pch.h

SOURCES += \
    node_item.cpp \
    node_model.cpp \
    node_sort_model.cpp \
    port_spin_box.cpp \
    node_type_proxy_model.cpp \
    node_check_model.cpp \
    node_item_model.cpp \
    actions.cpp \
    data_combo_box.cpp \
    device_proxy_model.cpp \
    pass_line_edit.cpp \
    splash_screen.cpp

DISTFILES += \
    widgets.pri

TRANSLATIONS += \
    ../../../translations/libs/widgets_ru.ts \

RESOURCES += \
    $$PWD/res.qrc

include($$(PRO_ROOT)/src/common/common.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/libs/utils/utils.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
