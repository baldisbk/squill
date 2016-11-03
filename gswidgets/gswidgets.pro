#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T20:32:57
#
#-------------------------------------------------

QT       += widgets

TEMPLATE = lib

CONFIG         += plugin
INCLUDEPATH    += ../gscore
TARGET          = $$qtLibraryTarget(gswidgets)
DESTDIR         = ../plugins

SOURCES += gswidgets.cpp \
    gstable.cpp \
    gslineedit.cpp \
    gslabel.cpp \
    gsdelegate.cpp \
    gscombobox.cpp \
    gscolumn.cpp \
    gsbutton.cpp

HEADERS += gswidgets.h \
    gstable.h \
    gslineedit.h \
    gslabel.h \
    gsdelegate.h \
    gscombobox.h \
    gscolumn.h \
    gsbutton.h

LIBS += -L.. -lgscore
