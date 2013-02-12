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
  feature.h \
    gui/jobmatrix.h \
    gui/mylabel.h \
    gui/mainviewer.h

SOURCES += \
  main.cpp \
  archiveloader.cpp \
  odbppviewwidget.cpp \
  feature.cpp \
    gui/jobmatrix.cpp \
    gui/mylabel.cpp \
    gui/mainviewer.cpp

INCLUDEPATH += . .build parser parser/record symbol

DESTDIR = ../bin
TARGET = camview

FORMS += \
    gui/jobmatrix.ui \
    gui/mainviewer.ui
