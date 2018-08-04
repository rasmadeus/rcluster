TEMPLATE = \
    subdirs

SUBDIRS += \
    libs \
    core \
    plugins \
    tests

core.depends = libs
slaves.depends = libs
tests.depends = libs
