include($$PWD/install.pri)
include($$PWD/version.pri)

CONFIG += \
    skip_target_version_ext

DESTDIR = \
    $$joinPath($$(OUT_DIR), $$getConfig())
