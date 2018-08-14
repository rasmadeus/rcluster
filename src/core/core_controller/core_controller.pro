TARGET = \
    core_controller

TEMPLATE = \
    app

QT += \
    core \
    gui \
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
    main_view.h \
    config_view.h \
    slave_params_view.h \
    name_dialog.h \
    slave_editor.h \
    empty_slave_editor.h \
    config_view_menu.h \
    core_actions.h

SOURCES += \
    main.cpp \
    main_view.cpp \
    config_view.cpp \
    slave_params_view.cpp \
    name_dialog.cpp \
    slave_editor.cpp \
    empty_slave_editor.cpp \
    config_view_menu.cpp \
    core_actions.cpp

RESOURCES += \
    res.qrc

TRANSLATIONS += \
    ../../translations/core_controller_ru.ts \

include($$(PRO_ROOT)/src/common/boost.pri)
include($$(PRO_ROOT)/src/libs/utils/utils.pri)
include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/libs/transport/transport.pri)
include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/common/install_app.pri)
