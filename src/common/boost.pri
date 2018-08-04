DEFINES += \
    BOOST_ALL_DYN_LINK

INCLUDEPATH += \
    $$(BOOST_HOME)

LIBS += \
    -L$$(BOOST_HOME)/lib

win32 {
    CONFIG(debug, debug|release) {
        LIBS += \
            -llibboost_system-mgw53-mt-d-x32-1_67.dll \
            -llibboost_date_time-mgw53-mt-d-x32-1_67.dll \
            -llibboost_filesystem-mgw53-mt-d-x32-1_67.dll \
            -llibboost_thread-mgw53-mt-d-x32-1_67.dll \
            -llibboost_log-mgw53-mt-d-x32-1_67.dll \
            -llibboost_log_setup-mgw53-mt-d-x32-1_67.dll
    }

    CONFIG(release, debug|release) {
        LIBS += \
            -llibboost_system-mgw53-mt-x32-1_67.dll \
            -llibboost_filesystem-mgw53-mt-x32-1_67.dll \
            -llibboost_date_time-mgw53-mt-x32-1_67.dll \
            -llibboost_thread-mgw53-mt-x32-1_67.dll \
            -llibboost_log-mgw53-mt-x32-1_67.dll \
            -llibboost_log_setup-mgw53-mt-x32-1_67.dll
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
