TEMPLATE = subdirs
SUBDIRS = main \
    gswidgets \
    gscore \
    gsdb \
    gsqml

gswidgets.depends = gscore
gsqml.depends = gscore
gsdb.depends = gscore
main.depends = gscore
