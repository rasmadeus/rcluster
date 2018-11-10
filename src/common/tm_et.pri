QT += \
    gui \
    core \
    widgets \
    network

INCLUDEPATH += \
    $$(TM_LIBS)/include/eyestracker

CONFIG(debug, debug|release) {
    LIBS += \
        -L$$(TM_LIBS)/debug
}

CONFIG(release, debug|release) {
    LIBS += \
        -L$$(TM_LIBS)/release
}

LIBS += \
    -leyestracker1