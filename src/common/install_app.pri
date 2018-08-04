include($$PWD/install.pri)
include($$PWD/version.pri)

DESTDIR = \
    $$joinPath($$(OUT_DIR), $$getConfig())

RC_ICONS = res/icon.ico
