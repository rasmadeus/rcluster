unix {
    CONFIG += \
        link_pkgconfig

    INCLUDEPATH += \
        $$(GSTREAMER_HOME)/include/gstreamer-1.0

    PKGCONFIG += \
        gstreamer-1.0 \
        glib-2.0 \
        gobject-2.0 \
        gstreamer-rtsp-1.0 \
        gstreamer-video-1.0 \
        gstreamer-rtsp-server-1.0
}

win32 {
    INCLUDEPATH += \
        $$(GSTREAMER_HOME)/include/gstreamer-1.0 \
        $$(GSTREAMER_HOME)/include/glib-2.0 \
        $$(GSTREAMER_HOME)/lib/glib-2.0/include

    LIBS += \
        -L$$(GSTREAMER_HOME)/lib \
        -lgstreamer-1.0 \
        -lglib-2.0 \
        -lintl \
        -lgobject-2.0 \
        -lgstvideo-1.0 \
        -lgstbase-1.0 \
        -lgstrtsp-1.0 \
        -lgstrtspserver-1.0
}
