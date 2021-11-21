HOME = ../..
include($$HOME/common.pri)

TEMPLATE = lib
TARGET = pdCalcBackend
DEPENDPATH += .
INCLUDEPATH += . $$HOME/src
unix: DESTDIR = $$HOME/lib
win32: DESTDIR = $$HOME/bin

win32: DEFINES += _USE_MATH_DEFINES

HEADERS += \
    appobserver.h \
    command.h \
    commanddispatcher.h \
    commandmanager.h \
    commandrepository.h \
    corecommand.h \
    stack.h

SOURCES += \
    appobserver.cpp \
    command.cpp \
    commanddispatcher.cpp \
    commandmanager.cpp \
    commandrepository.cpp \
    corecommand.cpp \
    stack.cpp

unix:LIBS += -ldl
win32:LIBS += -L$$HOME/bin -lpdCalcUtilities1
