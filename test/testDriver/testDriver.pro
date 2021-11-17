HOME = ../..
include ($$HOME/common.pri)
QMAKE_CXXFLAGS += -Wno-deprecated-declarations
TEMPLATE = app
TARGET = testPdCalc
INCLUDEPATH += $$HOME $$HOME/src
DESTDIR = $$HOME/bin

QT += testlib

SOURCES += main.cpp

unix: LIBS += -L$$HOME/lib -lpdCalcUtilities -lpdCalcUtilitiesTest \
        -lpdCalcBackend -lpdCalcBackendTest

win32:LIBS += -L$$HOME/bin -lpdCalcUtilities1 -lpdCalcUtilitiesTest1 \
        -lpdCalcBackend1 -lpdCalcBackendTest1
