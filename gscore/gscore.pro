#-------------------------------------------------
#
# Project created by QtCreator 2016-11-01T11:08:58
#
#-------------------------------------------------

QT       += qml

TEMPLATE = lib
DESTDIR = ..

DEFINES += GSCORE_LIBRARY

SOURCES += \
    sourceparser.cpp \
    gsobject.cpp \
    gswidget.cpp \
    gscontext.cpp

HEADERS +=\
    sourceparser.h \
    gsobject.h \
    gswidget.h \
    gscontext.h \
    gscore.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
