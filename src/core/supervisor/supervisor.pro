TARGET = \
    supervisor

TEMPLATE = \
    app

QT += \
    gui \
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

include($$(PRO_ROOT)/src/common/boost.pri)
include($$(PRO_ROOT)/src/common/globals.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/libs/transport/transport.pri)
include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/common/install_app.pri)
