TARGET = \
    widgets

TEMPLATE = \
    lib

DEFINES += \
    WIDGETS_LIBRARY

CONFIG += \
    c++14 \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    widgets_global.h \
    slave_item.h \
    slave_model.h \
    slave_model_check.h \
    slave_sort_model.h \
    actions.h \
    port_spin_box.h \
    data_combo_box.h
    pch.h

SOURCES += \
    slave_item.cpp \
    slave_model.cpp \
    slave_model_check.cpp \
    slave_sort_model.cpp \
    actions.cpp \
    port_spin_box.cpp \
    data_comb_obox.cpp

DISTFILES += \
    widgets.pri

include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
