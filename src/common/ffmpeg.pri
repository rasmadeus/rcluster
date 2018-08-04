INCLUDEPATH += \
    $$(FFMPEG_HOME)/include

LIBS += \
    -L$$(FFMPEG_HOME)/lib

win32 {
    LIBS += \
        -lavdevice \
        -lpsapi \
        -lole32 \
        -lstrmiids \
        -luuid \
        -loleaut32 \
        -lshlwapi \
        -lgdi32 \
        -lm \
        -lvfw32\
}
