TEMPLATE = \
    subdirs

SUBDIRS += \
    transport \
    config \
    plugin \
    widgets \
    utils \
    multimedia

config.depends = transport
transport.depends = utils
plugin.depends = utils
multimedia.depends = utils
widgets.depends = utils config plugin
