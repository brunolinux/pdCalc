HOME = ../..
include($$HOME/common.pri)
TEMPLATE = lib
TARGET = pdCalcUtilities
DEPENDPATH += .
INCLUDEPATH += . $$HOME/src
unix:DESTDIR = $$HOME/lib
win32:DESTDIR = $$HOME/bin

DEFINES += BUILDING_UTILITIES

HEADERS += \
    exception.h \
    observer.h \
    publisher.h

SOURCES += \
    observer.cpp \
    publisher.cpp
