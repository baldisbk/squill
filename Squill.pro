TEMPLATE = app

QT += qml quick core gui widgets sql

SOURCES += main.cpp \
    sourceparser.cpp \
    gsobject.cpp \
    gsbutton.cpp \
    gswidget.cpp \
    gscontext.cpp \
    gslabel.cpp \
    gslineedit.cpp \
    gsmainwindow.cpp \
    gsdatabase.cpp \
    gsquery.cpp \
    gstable.cpp \
    gscolumn.cpp \
    gscombobox.cpp \
    gsdelegate.cpp

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
    gsmainwindow.h \
    gsdatabase.h \
    gsquery.h \
    gstable.h \
    gscolumn.h \
    gscombobox.h \
    gsdelegate.h

DISTFILES += \
    test.xml
