TEMPLATE = app

QT += qml quick core gui widgets

SOURCES += main.cpp \
    sourceparser.cpp \
    gsobject.cpp \
    gsbutton.cpp \
    gswidget.cpp \
    gscontext.cpp \
    gslabel.cpp \
    gslineedit.cpp \
    gsmainwindow.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    sourceparser.h \
    gsobject.h \
    gsbutton.h \
    gswidget.h \
    gscontext.h \
    gslabel.h \
    gslineedit.h \
    gsmainwindow.h

DISTFILES += \
    test.xml
