QT  += \
    core \
    svg

TARGET = \
    utils

TEMPLATE = \
    lib

DEFINES += \
    UTILS_LIBRARY

CONFIG += \
    c++14 \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    translator.h \
    utils_global.h \
    crash_handler.h \
    log.h \
    globals.h \
    qt_types_hash.h \
    storable.h \
    svg.h \
    device.h \
    active_device.h \
    device_state.h
    pch.h

SOURCES += \
    translator.cpp \
    crash_handler.cpp \
    log.cpp \
    storable.cpp \
    device.cpp \
    active_device.cpp \
    device_state.cpp

DISTFILES += \
    utils.pri

TRANSLATIONS += \
    ../../translations/libs/utils_ru.ts \

include($$(PRO_ROOT)/src/common/boost.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
