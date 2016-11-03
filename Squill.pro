TEMPLATE = subdirs
SUBDIRS = main \
    gswidgets \
    gscore

gswidgets.depends = gscore
main.depends = gscore
