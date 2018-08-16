INCLUDEPATH += \
    $$(FFMPEG_HOME)/include

LIBS += \
    -L$$(FFMPEG_HOME)/lib

win32 {
    LIBS += \
        -lavcodec.dll \
        -lavdevice.dll \
        -lavfilter.dll \
        -lavformat.dll \
        -lavutil.dll \
        -lpostproc.dll \
        -lswresample.dll \
        -lswscale.dll
}
