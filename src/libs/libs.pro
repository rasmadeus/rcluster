TEMPLATE = \
    subdirs

SUBDIRS += \
    transport \
    config \
    plugin \
    widgets

config.depends = transport
widgets.depends = config plugin
