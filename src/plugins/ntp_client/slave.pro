TARGET = \
    ntp_client

TEMPLATE = \
    app

QT += \
    core \
    gui \
    network

CONFIG -= \
    app_bundle

CONFIG += \
    console \
    c++14 \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    ntp_packet.h \
    ntp_timestamp.h \
    ntp_client.h \
    ntp_reply.h \
    ntp.h \
    ntp_reply_p.h \
    controller.h

SOURCES += \
    main.cpp \
    ntp_client.cpp \
    ntp_reply.cpp \
    controller.cpp

RESOURCES += \
    res.qrc

TRANSLATIONS += \
    ../../../translations/ntp_client_ru.ts \

include($$(PRO_ROOT)/src/common/boost.pri)
include($$(PRO_ROOT)/src/common/globals.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/transport/transport.pri)
include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/common/install_app.pri)
