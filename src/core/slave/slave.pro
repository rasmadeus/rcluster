TARGET = \
    slave

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
    args.h

SOURCES += \
    main.cpp \
    args.cpp

RESOURCES += \
    res.qrc

TRANSLATIONS += \
    ../../../translations/common/slave_ru.ts \

include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/common/install_app.pri)
