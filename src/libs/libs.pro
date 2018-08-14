TEMPLATE = \
    subdirs

SUBDIRS += \
    transport \
    config \
    plugin \
    widgets \
    utils

config.depends = transport utils
widgets.depends = config plugin utils
