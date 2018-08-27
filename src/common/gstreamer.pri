unix {
    GSTREAMER_HOME_INCLUDE = /usr/include/gstreamer-1.0

    CONFIG += \
        link_pkgconfig

    INCLUDEPATH += \
        $$GSTREAMER_HOME_INCLUDE

    PKGCONFIG += \
        gstreamer-1.0 \
        glib-2.0 \
        gobject-2.0 \
        gstreamer-rtsp-1.0 \
        gstreamer-rtsp-server-1.0
}
