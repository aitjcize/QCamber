include (odbpp/odbpp.pri)

HEADERS += \
  parser/parser.h \
  parser/record.h \
  parser/code39.h \
  parser/featuresdatastore.h \
  parser/fontdatastore.h \
  parser/datastore.h \
  parser/notesdatastore.h \
  parser/structuredtextdatastore.h

SOURCES += \
  parser/parser.cpp \
  parser/surfacerecord.cpp \
  parser/textrecord.cpp \
  parser/padrecord.cpp \
  parser/linerecord.cpp \
  parser/barcoderecord.cpp \
  parser/arcrecord.cpp \
  parser/charrecord.cpp \
  parser/noterecord.cpp \
  parser/code39.cpp \
  parser/featuresdatastore.cpp \
  parser/fontdatastore.cpp \
  parser/notesdatastore.cpp \
  parser/structuredtextdatastore.cpp
