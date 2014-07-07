QT += qml quick widgets

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    programlistmodel.cpp

DESTDIR = ../bin

OTHER_FILES += \
    qml/main.qml \
    qml/shared/Button.qml \
    qml/shared/CheckBox.qml \
    qml/shared/LauncherList.qml \
    qml/shared/SimpleLauncherDelegate.qml \
    qml/shared/Slider.qml \
    qml/shared/TabSet.qml \
    qml/shared/TextField.qml

RESOURCES += \
    listexe.qrc \
    shared.qrc \
    content.qrc

HEADERS += \
    programlistmodel.h
