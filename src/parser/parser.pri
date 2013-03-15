include (flex.pri)
include (bison.pri)
include (record/record.pri)

HEADERS += \
  parser/cachedparser.h \
  parser/featuresparser.h \
  parser/fontparser.h \
  parser/notesparser.h \
  parser/parser.h \
  parser/structuredtextparser.h \
  parser/yyheader.h

SOURCES += \
  parser/featuresparser.cpp \
  parser/fontparser.cpp \
  parser/notesparser.cpp \
  parser/parser.cpp \
  parser/structuredtextparser.cpp

FLEXSOURCES += parser/db.l
BISONSOURCES += parser/db.y
