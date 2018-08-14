QT += \
    gui \
    core \
    widgets \
    network

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
    -ltransport

include($$(PRO_ROOT)/src/libs/utils/utils.pri)
