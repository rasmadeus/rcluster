INCLUDEPATH += \
    $$(ZLIB_HOME)/include
	
CONFIG(debug, debug|release) {
    LIBS += \
        -L$$(ZLIB_HOME)/lib/debug
}

CONFIG(release, debug|release) {
    LIBS += \
        -L$$(ZLIB_HOME)/lib/release
}

LIBS += \
    -lzlibwapi	
	
DEFINES += \
	ZLIB_WINAPI