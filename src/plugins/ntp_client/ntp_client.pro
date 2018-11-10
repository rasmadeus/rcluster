TARGET = \
    ntp_client

TEMPLATE = \
    lib

CONFIG += \
    precompile_header \
    warn_on \
    plugin \
    no_plugin_name_prefix

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    ntp_client_editor.h \
    ntp_client_plugin.h \
    controller.h \
    ntp.h \
    ntp_client.h \
    ntp_packet.h \
    ntp_reply.h \
    ntp_reply_p.h \
    ntp_timestamp.h

SOURCES += \
    ntp_client_editor.cpp \
    ntp_client_plugin.cpp \
    controller.cpp \
    ntp_client.cpp \
    ntp_reply.cpp

RESOURCES += \
    $$PWD/res.qrc

TRANSLATIONS += \
    ../../../translations/plugins/ntp_client_ru.ts \

include($$(PRO_ROOT)/src/common/common.pri)	
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_plugin.pri)
