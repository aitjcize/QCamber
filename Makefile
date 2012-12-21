LEX	 = lex
YACC	 = bison -d -t -v
CXXFLAGS = -g
LIBS 	 = -lfl -ly

OBJS 	 = parser.o main.o
PARSER_FILES  = lex.yy.c kvt.tab.c

main: kvt.tab.c lex.yy.c $(OBJS)
	$(CXX) $(CXXFLAGS) $(PARSER_FILES) $(OBJS) $(LIBS) -o test

lex.yy.c: kvt.l kvt.tab.c
	$(LEX) kvt.l

kvt.tab.c: kvt.y
	$(YACC) kvt.y

clean:
	rm -f $(OBJS) kvt.tab.* lex.yy.c
