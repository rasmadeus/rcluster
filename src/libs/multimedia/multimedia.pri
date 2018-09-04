QT += \
    core \
    gui \
    widgets

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
    -lmultimedia

include($$(PRO_ROOT)/src/common/gstreamer.pri)
