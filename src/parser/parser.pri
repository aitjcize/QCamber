include (flex.pri)
include (bison.pri)
include (record/record.pri)

HEADERS += \
  parser/yyheader.h \
  parser/parser.h \
  parser/structuredtextparser.h \
  parser/featuresparser.h \
  parser/fontparser.h \
  parser/notesparser.h

SOURCES += \
  parser/parser.cpp \
  parser/structuredtextparser.cpp \
  parser/featuresparser.cpp \
  parser/fontparser.cpp \
  parser/notesparser.cpp

FLEXSOURCES += parser/db.l
BISONSOURCES += parser/db.y
