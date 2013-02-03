HEADERS += \
  parser/yyheader.h

FLEXSOURCES += parser/db.l
BISONSOURCES += parser/db.y

# Flex settings
flex.commands = flex -o$${BUILD_DIR}/${QMAKE_FILE_IN_BASE}.lex.cpp ${QMAKE_FILE_IN}
flex.CONFIG += target_predeps
flex.input = FLEXSOURCES
flex.output = $${BUILD_DIR}/db.lex.cpp
flex.variable_out = SOURCES
flex.depends = $${BUILD_DIR}/db.tab.h
flex.name = flex
QMAKE_EXTRA_COMPILERS += flex
 
# Bison settings
bison.commands = bison -t -v ${QMAKE_FILE_IN} -o $${BUILD_DIR}/${QMAKE_FILE_IN_BASE}.tab.cpp --defines=$${BUILD_DIR}/${QMAKE_FILE_IN_BASE}.tab.h
bison.CONFIG += target_predeps
bison.input = BISONSOURCES
bison.output = $${BUILD_DIR}/db.tab.cpp
bison.clean = $${BUILD_DIR}/db.tab.cpp $${BUILD_DIR}/db.tab.h $${BUILD_DIR}/db.output
bison.variable_out = SOURCES
bison.name = bison
QMAKE_EXTRA_COMPILERS += bison

bisonheader.commands = @true
bisonheader.CONFIG += target_predeps
bisonheader.input = BISONSOURCES
bisonheader.output = $${BUILD_DIR}/db.tab.h
bisonheader.variable_out = HEADERS
bisonheader.name = bison header
bisonheader.depends = $${BUILD_DIR}/db.tab.cpp
QMAKE_EXTRA_COMPILERS += bisonheader
