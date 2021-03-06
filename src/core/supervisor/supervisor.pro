TARGET = \
    supervisor

TEMPLATE = \
    app

CONFIG += \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    tray_icon.h \
    supervisors.h \
    supervisor.h

SOURCES += \
    main.cpp \
    tray_icon.cpp \
    supervisors.cpp \
    supervisor.cpp

RESOURCES += \
    res.qrc

TRANSLATIONS += \
    ../../translations/supervisor_ru.ts \

include($$(PRO_ROOT)/src/common/common.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_app.pri)
