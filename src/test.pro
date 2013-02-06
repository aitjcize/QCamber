TEMPLATE = app

MOC_DIR = .build
UI_DIR = .build
RCC_DIR = .build
OBJECTS_DIR = .build
BUILD_DIR = .build

include (parser/parser.pri)
include (symbol/symbol.pri)
include (tests/tests.pri)

HEADERS += \
  archiveloader.h \
  symbolfactory.h \
  feature.h \

SOURCES += \
  archiveloader.cpp \
  feature.cpp

INCLUDEPATH += . .build parser parser/record symbol

DESTDIR = ../bin
TARGET = test
