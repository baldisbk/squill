TEMPLATE = subdirs
SUBDIRS = main \
    gswidgets \
    gscore \
    gsdb \
    gsqml \
    editor

gswidgets.depends = gscore
gsqml.depends = gscore
gsdb.depends = gscore
main.depends = gscore
