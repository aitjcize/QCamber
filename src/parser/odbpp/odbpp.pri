include (flex.pri)
include (bison.pri)

HEADERS += \
  parser/odbpp/cachedparser.h \
  parser/odbpp/featuresparser.h \
  parser/odbpp/featuresdatastore.h \
  parser/odbpp/fontparser.h \
  parser/odbpp/fontdatastore.h \
  parser/odbpp/notesparser.h \
  parser/odbpp/datastore.h \
  parser/odbpp/notesdatastore.h \
  parser/odbpp/parser.h \
  parser/odbpp/structuredtextparser.h \
  parser/odbpp/structuredtextdatastore.h \
  parser/odbpp/yyheader.h

SOURCES += \
  parser/odbpp/featuresparser.cpp \
  parser/odbpp/featuresdatastore.cpp \
  parser/odbpp/fontparser.cpp \
  parser/odbpp/fontdatastore.cpp \
  parser/odbpp/notesparser.cpp \
  parser/odbpp/notesdatastore.cpp \
  parser/odbpp/parser.cpp \
  parser/odbpp/structuredtextparser.cpp \
  parser/odbpp/structuredtextdatastore.cpp

FLEXSOURCES += parser/odbpp/db.l
BISONSOURCES += parser/odbpp/db.y
