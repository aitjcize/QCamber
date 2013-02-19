TEMPLATE = app

MOC_DIR = .build
UI_DIR = .build
RCC_DIR = .build
OBJECTS_DIR = .build
BUILD_DIR = .build

include (parser/parser.pri)
include (symbol/symbol.pri)
include (gui/gui.pri)

HEADERS += \
  archiveloader.h \
  config.h \
  context.h \
  feature.h \
  layergraphicseffect.h \
  odbppgraphicsscene.h \
  odbppgraphicsview.h \
  profile.h \
  symbolfactory.h

SOURCES += \
  archiveloader.cpp \
  feature.cpp \
  config.cpp \
  main.cpp \
  odbppgraphicsscene.cpp \
  odbppgraphicsview.cpp \
  layergraphicseffect.cpp \
  profile.cpp

INCLUDEPATH += . .build parser parser/record symbol gui

DESTDIR = ../bin
TARGET = camview
