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

HEADERS += \
  archiveloader.h \
  context.h \
  macros.h \
  settings.h \
  symbolpool.h

SOURCES += \
  archiveloader.cpp \
  context.cpp \
  main.cpp \
  settings.cpp \
  symbolpool.cpp

RESOURCES += \
    resources.qrc

INCLUDEPATH += . .build parser parser/record symbol gui graphicsview

DESTDIR = ../bin
TARGET = qcamber

# Product information
VERSION = 0.1.0
QMAKE_TARGET_PRODUCT = "QCamber"
QMAKE_TARGET_DESCRIPTION = ""
QMAKE_TARGET_COPYRIGHT = "Copyrights(c) 2013 QCamber Authors"
