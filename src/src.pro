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
  context.h \
  feature.h \
  layergraphicseffect.h \
  layer.h \
  notes.h \
  odbppgraphicsscene.h \
  odbppgraphicsview.h \
  profile.h \
  settings.h \
  symbolfactory.h

SOURCES += \
  archiveloader.cpp \
  context.cpp \
  feature.cpp \
  layer.cpp \
  layergraphicseffect.cpp \
  main.cpp \
  notes.cpp \
  odbppgraphicsscene.cpp \
  odbppgraphicsview.cpp \
  profile.cpp \
  settings.cpp

RESOURCES += \
  ../resources.qrc

INCLUDEPATH += . .build parser parser/record symbol gui

DESTDIR = ../bin
TARGET = camview
