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
  config.h \
  context.h \
  feature.h \
  layergraphicseffect.h \
  layer.h \
  notes.h \
  odbppgraphicsscene.h \
  odbppgraphicsview.h \
  profile.h \
  symbolfactory.h

SOURCES += \
  archiveloader.cpp \
  config.cpp \
  feature.cpp \
  layer.cpp \
  notes.cpp \
  layergraphicseffect.cpp \
  odbppgraphicsscene.cpp \
  odbppgraphicsview.cpp \
  profile.cpp

INCLUDEPATH += . .build parser parser/record symbol

DESTDIR = ../bin
TARGET = test
