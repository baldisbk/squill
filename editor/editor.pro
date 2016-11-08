#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T22:00:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = ..
TARGET = squill_edit
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH    += ../gscore
LIBS += -L.. -lgscore

CONFIG += mobility
MOBILITY =
