QT += \
    testlib

QT -= \
    gui

TARGET = \
    config_test

CONFIG += \
    console \
    c++14 \
    warn_on

CONFIG -= \
    app_bundle

TEMPLATE = \
    app

DEFINES += \
    QT_DEPRECATED_WARNINGS

SOURCES += \
    config_test.cpp

include($$(PRO_ROOT)/src/libs/config/config.pri)
