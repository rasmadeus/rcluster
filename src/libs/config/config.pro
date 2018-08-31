TARGET = \
    config

TEMPLATE = \
    lib

DEFINES += \
    CONFIG_LIBRARY

CONFIG += \
    c++14 \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    storage.h \
    config.h \
    slave.h \
    config_global.h \
    file_storable.h \
    config_watcher.h \
    slave_as_params.h

SOURCES += \
    storage.cpp \
    config.cpp \
    slave.cpp \
    file_storable.cpp \
    config_watcher.cpp \
    slave_as_params.cpp

DISTFILES += \
    config.pri

TRANSLATIONS += \
    ../../translations/libs/config_ru.ts

include($$(PRO_ROOT)/src/libs/transport/transport.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
