TARGET = \
    core_server

TEMPLATE = \
    app

QT += \
    core \
    network \
    widgets

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

include($$(PRO_ROOT)/src/common/boost.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/transport/transport.pri)
include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/libs/utils/utils.pri)
include($$(PRO_ROOT)/src/common/install_app.pri)
