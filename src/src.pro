TEMPLATE = app

MOC_DIR = .build
UI_DIR = .build
RCC_DIR = .build
OBJECTS_DIR = .build
BUILD_DIR = .build

include (parser/parser.pri)
include (symbol/symbol.pri)

HEADERS += \
  archiveloader.h \
  odbppviewwidget.h \
  symbolfactory.h \
  feature.h

SOURCES += \
  main.cpp \
  archiveloader.cpp \
  odbppviewwidget.cpp \
  feature.cpp

INCLUDEPATH += . .build parser symbol

DESTDIR = ../bin
TARGET = camview
