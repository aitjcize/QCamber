TEMPLATE = app
include (Parser/Parser.pri)
include (Gui/Gui.pri)
include (Symbol/Symbol.pri)
include (Build/Build.pri)
INCLUDEPATH += . .. Parser Gui Symbol
DESTDIR = ../bin
TARGET = camview
MOC_DIR = .build
UI_DIR = .build
RCC_DIR = .build
OBJECTS_DIR = .build
