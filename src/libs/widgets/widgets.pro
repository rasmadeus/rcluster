QT  += \
    gui \
    widgets \
    network

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
    menu.h \
    translator.h \
    slave_item.h \
    slave_model.h \
    slave_model_check.h \
    slave_sort_model.h
    pch.h

SOURCES += \
    menu.cpp \
    translator.cpp \
    slave_item.cpp \
    slave_model.cpp \
    slave_model_check.cpp \
    slave_sort_model.cpp

DISTFILES += \
    widgets.pri

include($$(PRO_ROOT)/src/common/boost.pri)
include($$(PRO_ROOT)/src/common/globals.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/libs/transport/transport.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
