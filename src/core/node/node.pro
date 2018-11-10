TARGET = \
    node

TEMPLATE = \
    app

CONFIG += \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    args.h \
    manager.h

SOURCES += \
    main.cpp \
    args.cpp \
    manager.cpp

RESOURCES += \
    res.qrc

TRANSLATIONS += \
    ../../../translations/common/node_ru.ts \

DESTFILES += \
    node.pro

include($$(PRO_ROOT)/src/common/common.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_app.pri)
