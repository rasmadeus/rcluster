TARGET = \
    core_server

TEMPLATE = \
    app

CONFIG += \
    c++14 \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    server.h \
    client.h \
    tray_icon.h \
    config_storage.h

SOURCES += \
    main.cpp \
    server.cpp \
    client.cpp \
    tray_icon.cpp \
    config_storage.cpp

RESOURCES += \
    res.qrc

TRANSLATIONS += \
    ../../translations/core_server_ru.ts \

include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_app.pri)
