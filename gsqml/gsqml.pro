#-------------------------------------------------
#
# Project created by QtCreator 2016-11-03T17:43:30
#
#-------------------------------------------------

QT       += widgets qml quick

TEMPLATE = lib

CONFIG         += plugin
INCLUDEPATH    += ../gscore
TARGET          = $$qtLibraryTarget(gsqml)
DESTDIR         = ../plugins

LIBS += -L.. -lgscore

SOURCES += gsqml.cpp \
    qmlcontainer.cpp \
    gsqmlwindow.cpp \
    gsqmlwidget.cpp \
    gsqmlitem.cpp

HEADERS += gsqml.h \
    qmlcontainer.h \
    gsqmlwindow.h \
    gsqmlwidget.h \
    gsqmlitem.h
