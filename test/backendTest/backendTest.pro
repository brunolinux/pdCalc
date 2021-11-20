HOME = ../..
include ($$HOME/common.pri)
TEMPLATE = lib
TARGET = pdCalcBackendTest
DEPENDPATH += $$HOME/src/shared
INCLUDEPATH += . $$HOME $$HOME/src
unix:DESTDIR = $$HOME/lib
win32:DESTDIR = $$HOME/bin
DEFINES += BACKEND_TEST_DIR=\\\"$$PWD\\\"
unix:DEFINES += PLUGIN_TEST_FILE=\\\"plugins.unix.pdp\\\"
win32:DEFINES += PLUGIN_TEST_FILE=\\\"plugin.win.pdp\\\"

HEADERS += \
    commanddispatchertest.h \
    commandmanagertest.h \
    commandrepositorytest.h \
    corecommandstest.h \
    stacktest.h

SOURCES += \
    commanddispatchertest.cpp \
    commandmanagertest.cpp \
    commandrepositorytest.cpp \
    corecommandstest.cpp \
    stacktest.cpp


unix:LIBS += -L$$HOME/lib -lpdCalcUtilities -lpdCalcBackend
win32:LIBS += -L$$HOME/bin -lpdCalcUtilities1 -lpdCalcBackend1

QT -= gui core
QT += testlib
