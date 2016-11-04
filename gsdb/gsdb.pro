#-------------------------------------------------
#
# Project created by QtCreator 2016-11-03T17:36:25
#
#-------------------------------------------------

QT       += sql
QT       -= gui

TEMPLATE = lib

CONFIG         += plugin
INCLUDEPATH    += ../gscore
TARGET          = $$qtLibraryTarget(gsdb)
DESTDIR         = ../plugins

LIBS += -L.. -lgscore

SOURCES += gsdb.cpp \
    gsquery.cpp \
    gsdatabase.cpp

HEADERS += gsdb.h\
    gsquery.h \
    gsdatabase.h

