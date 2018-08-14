QT += \
    gui \
    core \
    widgets \
    network

TARGET = \
    transport

TEMPLATE = \
    lib

DEFINES += \
    TRANSPORT_LIBRARY

CONFIG += \
    c++14 \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    transport_global.h \
    message.h \
    message_controller.h \
    message_router.h \
    core_connect_widget.h \
    core_bus.h
    pch.h

SOURCES += \
    message.cpp \
    message_controller.cpp \
    message_router.cpp \
    core_connect_widget.cpp \
    core_bus.cpp

DISTFILES += \
    transport.pri

TRANSLATIONS += \
    ../../translations/libs/transport_ru.ts \

include($$(PRO_ROOT)/src/common/globals.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
