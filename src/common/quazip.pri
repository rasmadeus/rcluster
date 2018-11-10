INCLUDEPATH += \
    $$(QUAZIP_HOME)/include/quazip

CONFIG(debug, debug|release) {
    LIBS += \
        -L$$(QUAZIP_HOME)/lib/debug

    LIBS += \
        -lquazipd
}

CONFIG(release, debug|release) {
    LIBS += \
        -L$$(QUAZIP_HOME)/lib/release

    LIBS += \
        -lquazip
}

include($$(PRO_ROOT)/src/common/zlib.pri)