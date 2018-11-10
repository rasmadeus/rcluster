DEFINES += \
    BOOST_ALL_DYN_LINK

INCLUDEPATH += \
    $$(BOOST_HOME)/include

LIBS += \
    -L$$(BOOST_HOME)/lib

win32 {
    CONFIG(debug, debug|release) {
        LIBS += \
            -lboost_system-vc141-mt-gd-x32-1_68 \
            -lboost_date_time-vc141-mt-gd-x32-1_68 \
            -lboost_filesystem-vc141-mt-gd-x32-1_68 \
            -lboost_thread-vc141-mt-gd-x32-1_68 \
            -lboost_log-vc141-mt-gd-x32-1_68 \
            -lboost_log_setup-vc141-mt-gd-x32-1_68
    }

    CONFIG(release, debug|release) {
        LIBS += \
            -lboost_system-vc141-mt-x32-1_68 \
            -lboost_filesystem-vc141-mt-x32-1_68 \
            -lboost_date_time-vc141-mt-x32-1_68 \
            -lboost_thread-vc141-mt-x32-1_68 \
            -lboost_log-vc141-mt-x32-1_68 \
            -lboost_log_setup-vc141-mt-x32-1_68
    }
}

unix {
    LIBS += \
        -lm \
        -ldl \
        -lboost_system \
        -lboost_date_time \
        -lboost_regex \
        -lboost_filesystem \
        -lboost_thread \
        -lboost_log \
        -lboost_log_setup
}
