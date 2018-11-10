include($$(PRO_ROOT)/src/common/install.pri)

TEMPLATE = \
    aux

INSTALLER = \
    rbarometer_setup

INPUT = \
    $$PWD/config/config.xml \
    $$PWD/packages

rbar.input = \
    INPUT

rbar.output = \
    $$joinPath($$joinPath($$(OUT_DIR), $$getConfig()), $$INSTALLER)

rbar.commands = \
    $$(QT_INSTALL_FRAMEWORK_BIN)/binarycreator -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}

rbar.CONFIG += \
    target_predeps \
    no_link \
    combine

QMAKE_EXTRA_COMPILERS += \
    rbar

DISTFILES += \
    $$PWD/packages/core/meta/package.xml \
    $$PWD/packages/core/meta/installscript.qs \
    $$PWD/config/config.xml
