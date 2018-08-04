INCLUDEPATH += \
    $$PWD

CONFIG(debug, debug|release) {
    LIBS += \
        -L$$(OUT_DIR)/debug
}

CONFIG(release, debug|release) {
    LIBS += \
        -L$$(OUT_DIR)/release
}

LIBS += \
    -lwidgets

include($$(PRO_ROOT)/src/libs/config/config.pri)
include($$(PRO_ROOT)/src/common/boost.pri)
include($$(PRO_ROOT)/src/common/globals.pri)
include($$(PRO_ROOT)/src/libs/plugin/plugin.pri)
include($$(PRO_ROOT)/src/libs/transport/transport.pri)
