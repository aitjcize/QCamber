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
  layerfeatures.h \
  graphicslayer.h \
  graphicslayerscene.h \
  layer.h \
  macros.h \
  measuregraphicsitem.h \
  notes.h \
  odbppgraphicsminimapview.h \
  odbppgraphicsscene.h \
  odbppgraphicsview.h \
  profile.h \
  settings.h \
  symbolfactory.h \
  symbolpool.h

SOURCES += \
  archiveloader.cpp \
  context.cpp \
  layerfeatures.cpp \
  graphicslayer.cpp \
  graphicslayerscene.cpp \
  layer.cpp \
  main.cpp \
  measuregraphicsitem.cpp \
  notes.cpp \
  odbppgraphicsscene.cpp \
  odbppgraphicsview.cpp \
  odbppgraphicsminimapview.cpp \
  profile.cpp \
  settings.cpp \
  symbolpool.cpp

INCLUDEPATH += . .build parser parser/record symbol gui

DESTDIR = ../bin
TARGET = qcamber

# Product information
VERSION = 0.1.0
QMAKE_TARGET_PRODUCT = "QCamber"
QMAKE_TARGET_DESCRIPTION = ""
QMAKE_TARGET_COPYRIGHT = "Copyrights(c) 2013 QCamber Authors"
