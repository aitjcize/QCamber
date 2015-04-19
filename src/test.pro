TEMPLATE = app

MOC_DIR = .build
UI_DIR = .build
RCC_DIR = .build
OBJECTS_DIR = .build
BUILD_DIR = .build

include (parser/parser.pri)
include (symbol/symbol.pri)
include (graphicsview/graphicsview.pri)
include (gui/gui.pri)
include (tests/tests.pri)

HEADERS += \
  archiveloader.h \
  context.h \
  macros.h \
  settings.h \
  symbolpool.h

SOURCES += \
  archiveloader.cpp \
  context.cpp \
  settings.cpp \
  symbolpool.cpp

INCLUDEPATH += . .build parser parser/record symbol gui graphicsview

DESTDIR = ../bin
TARGET = test
