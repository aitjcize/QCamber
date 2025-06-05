include (flex.pri)
include (bison.pri)

HEADERS += \
  parser/odbpp/cachedparser.h \
  parser/odbpp/featuresparser.h \
  parser/odbpp/fontparser.h \
  parser/odbpp/notesparser.h \
  parser/odbpp/packageparser.h \
  parser/odbpp/componentsparser.h \
  parser/odbpp/structuredtextparser.h \
  parser/odbpp/yyheader.h

SOURCES += \
  parser/odbpp/featuresparser.cpp \
  parser/odbpp/fontparser.cpp \
  parser/odbpp/notesparser.cpp \
  parser/odbpp/packageparser.cpp \
  parser/odbpp/componentsparser.cpp \
  parser/odbpp/structuredtextparser.cpp

FLEXSOURCES += parser/odbpp/db.l
BISONSOURCES += parser/odbpp/db.y
