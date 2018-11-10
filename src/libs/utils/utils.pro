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
    storable.h \
    svg.h \
    device.h \
    default_device.h \
    active_device.h \
    simplecrypt.h \
    hash_functions.h \
    device_writer.h \
    terminator.h \
    pch.h \
    eye_tracker.h

SOURCES += \
    translator.cpp \
    crash_handler.cpp \
    log.cpp \
    storable.cpp \
    device.cpp \
    default_device.cpp \
    active_device.cpp \
    simplecrypt.cpp \
    hash_functions.cpp \
    device_writer.cpp \
    terminator.cpp \
    eye_tracker.cpp

DISTFILES += \
    utils.pri

TRANSLATIONS += \
    ../../translations/libs/utils_ru.ts \

include($$(PRO_ROOT)/src/common/common.pri)
include($$(PRO_ROOT)/src/common/boost.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
