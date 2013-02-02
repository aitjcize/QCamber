HEADERS += \
  Parser/archiveloader.h \
  Parser/db.tab.h \
  Parser/parser.h \
  Parser/yyheader.h

SOURCES += \
  Parser/archiveloader.cpp \
  Parser/parser.cpp 

FLEXSOURCES += Parser/db.l
BISONSOURCES += Parser/db.y

# Flex settings
flex.commands = flex ${QMAKE_FILE_IN} && mv lex.yy.c lex.yy.cpp
flex.CONFIG += target_predeps
flex.input = FLEXSOURCES
flex.output = lex.yy.cpp
flex.variable_out = SOURCES
flex.depends = db.tab.h
flex.name = flex
QMAKE_EXTRA_COMPILERS += flex
 
# Bison settings
bison.commands = bison -d -t -v ${QMAKE_FILE_IN} && mv db.tab.c db.tab.cpp
bison.CONFIG += target_predeps
bison.input = BISONSOURCES
bison.output = db.tab.cpp
bison.clean = db.tab.cpp db.tab.h db.output
bison.variable_out = SOURCES
bison.name = bison
QMAKE_EXTRA_COMPILERS += bison

bisonheader.commands = @true
bisonheader.CONFIG += target_predeps
bisonheader.input = BISONSOURCES
bisonheader.output = db.tab.h
bisonheader.variable_out = HEADERS
bisonheader.name = bison header
bisonheader.depends = db.tab.cpp
QMAKE_EXTRA_COMPILERS += bisonheader
