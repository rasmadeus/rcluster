QT += \
    core \
    gui \
    widgets \
    multimedia

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

DEFINES += \
    __STDC_CONSTANT_MACROS

LIBS += \
    -lmultimedia

include($$(PRO_ROOT)/src/common/gstreamer.pri)
