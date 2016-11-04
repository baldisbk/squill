TEMPLATE = app

QT += widgets

SOURCES += main.cpp
INCLUDEPATH    += ../gscore

# Default rules for deployment.
include(deployment.pri)

TARGET = squill
DESTDIR = ..
LIBS += -L.. -lgscore
