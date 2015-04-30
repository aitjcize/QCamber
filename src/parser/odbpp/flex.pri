# Flex settings
flex.commands = flex -o$${BUILD_DIR}/${QMAKE_FILE_IN_BASE}.lex.cpp ${QMAKE_FILE_IN}
flex.CONFIG += target_predeps
flex.input = FLEXSOURCES
flex.output = $${BUILD_DIR}/db.lex.cpp
flex.variable_out = SOURCES
flex.depends = $${BUILD_DIR}/db.tab.h
flex.name = flex
QMAKE_EXTRA_COMPILERS += flex
