TARGET = \
    core_controller

TEMPLATE = \
    app

CONFIG += \
    precompile_header \
    warn_on

PRECOMPILED_HEADER = \
    pch.h

HEADERS += \
    pch.h \
    main_view.h \
    config_view.h \
    node_params_view.h \
    name_dialog.h \
    node_editor.h \
    empty_node_editor.h \
    config_view_menu.h \
    core_actions.h

SOURCES += \
    main.cpp \
    main_view.cpp \
    config_view.cpp \
    node_params_view.cpp \
    name_dialog.cpp \
    node_editor.cpp \
    empty_node_editor.cpp \
    config_view_menu.cpp \
    core_actions.cpp

RESOURCES += \
    res.qrc

DESTFILES += \
    core_controller.pro

TRANSLATIONS += \
    ../../translations/core_controller_ru.ts \

include($$(PRO_ROOT)/src/common/common.pri)
include($$(PRO_ROOT)/src/libs/widgets/widgets.pri)
include($$(PRO_ROOT)/src/common/install_app.pri)
