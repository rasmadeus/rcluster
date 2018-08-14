QT += \
    svg

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
    -lutils

include($$(PRO_ROOT)/src/common/boost.pri)
include($$(PRO_ROOT)/src/common/globals.pri)
