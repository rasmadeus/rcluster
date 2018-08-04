include($$(PRO_ROOT)/src/common/install.pri)

TEMPLATE = \
    aux

INSTALLER = \
    rcluster_setup

INPUT = \
    $$PWD/config/config.xml \
    $$PWD/packages

rcluster.input = \
    INPUT

rcluster.output = \
    $$joinPath($$joinPath($$(OUT_DIR), $$getConfig()), $$INSTALLER)

rcluster.commands = \
    $$(QT_INSTALL_FRAMEWORK_BIN)/binarycreator -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}

rcluster.CONFIG += \
    target_predeps \
    no_link \
    combine

QMAKE_EXTRA_COMPILERS += \
    rcluster

DISTFILES += \
    packages/core/meta/package.xml
