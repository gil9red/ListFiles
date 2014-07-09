QT += qml xml quick widgets

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    filelistmodel.cpp \
    fileiconimageprovider.cpp \
    filelistmanager.cpp \
    editfileitem.cpp \
    fileitem.cpp

HEADERS += \
    filelistmodel.h \
    fileiconimageprovider.h \
    filelistmanager.h \
    editfileitem.h \
    fileitem.h \
    utils.h

DESTDIR = ../bin

TARGET = ListFiles

RESOURCES += \
    listfiles.qrc

FORMS += \
    editfileitem.ui
