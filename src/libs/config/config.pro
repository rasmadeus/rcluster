TARGET = \
    config

TEMPLATE = \
    lib

DEFINES += \
    CONFIG_LIBRARY

CONFIG += \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    storage.h \
    config.h \
    node.h \
    config_global.h \
    file_storable.h \
    config_watcher.h

SOURCES += \
    storage.cpp \
    config.cpp \
    node.cpp \
    file_storable.cpp \
    config_watcher.cpp

DESTFILES += \
    config.pri

TRANSLATIONS += \
    ../../translations/libs/config_ru.ts

include($$(PRO_ROOT)/src/common/common.pri)
include($$(PRO_ROOT)/src/libs/transport/transport.pri)
include($$(PRO_ROOT)/src/common/install_lib.pri)
