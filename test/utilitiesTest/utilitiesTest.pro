HOME = ../..
include ($$HOME/common.pri)
TEMPLATE = lib
TARGET = pdCalcUtilitiesTest
DEPENDPATH += $$HOME/src/utilities
INCLUDEPATH += . $$HOME
unix: DESTDIR = $$HOME/lib
win32: DESTDIR = $$HOME/bin

QT -= gui core
QT += testlib

HEADERS += \
    publisherobservertest.h \
    tokenizertest.h

SOURCES += \
    publisherobservertest.cpp \
    tokenizertest.cpp

unix:LIBS += -L$$HOME/lib -lpdCalcUtilities
win32:LIBS += -L$$HOME/bin -lpdCalcUtilities1
