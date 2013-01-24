LEX	 = lex
YACC	 = bison -d -t -v
CXXFLAGS = -g
LIBS 	 = -lfl -ly

OBJS 	 = parser.o main.o
PARSER_FILES  = lex.yy.c db.tab.c

main: db.tab.c lex.yy.c $(OBJS)
	$(CXX) $(CXXFLAGS) $(PARSER_FILES) $(OBJS) $(LIBS) -o test

lex.yy.c: db.l db.tab.c
	$(LEX) db.l

db.tab.c: db.y
	$(YACC) db.y

clean:
	rm -f $(OBJS) db.tab.* lex.yy.c
