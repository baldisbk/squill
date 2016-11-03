TEMPLATE = app

QT += qml quick core gui widgets sql

SOURCES += main.cpp \
    gsdatabase.cpp \
    gsquery.cpp \
    gsqmlitem.cpp \
    gsqmlwidget.cpp \
    qmlcontainer.cpp \
    gsqmlwindow.cpp \
    gsmainwindow.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

INCLUDEPATH    += ../gscore

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    gsdatabase.h \
    gsquery.h \
    gsqmlitem.h \
    gsqmlwidget.h \
    qmlcontainer.h \
    gsqmlwindow.h \
    gsmainwindow.h

TARGET = squill
DESTDIR = ..
LIBS += -L.. -lgscore
