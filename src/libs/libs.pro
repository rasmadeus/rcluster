TEMPLATE = \
    subdirs

SUBDIRS += \
    transport \
    config \
    plugin \
    widgets \
    utils

config.depends = transport
transport.depends = utils
plugin.depends = utils
