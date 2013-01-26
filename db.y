%{
#include "yyheader.h"
#include <stdio.h>

#include "parser.h"

struct yycontext yyctx;

void putKeyValue(const char* key, const char* value);
int yyerror(const char* s);
int yylex(void);
%}

%token VAR
%token NL

%%

syntax       : op_newlines structures
             | op_newlines linerecords
             ;

structures   : structures structure
	     | structure
	     ;

structure    : VAR { yyctx.stdata->newElement($1); }
	       '{' op_newlines structures '}' newlines   {
                 yyctx.stdata->commitElement();
              }
	     | assignment
             ;

assignment   : VAR '=' VAR newlines { putKeyValue($1, $3); }
             | VAR '=' newlines     { putKeyValue($1, ""); }
             ;

linerecords  : linerecords linerecord { yyctx.lrdata->putLineRecord(); }
             | linerecord { yyctx.lrdata->putLineRecord(); }
             ;

linerecord   : terms newlines
             ;

terms        : terms VAR { yyctx.lrdata->putTerm($2); }
             | VAR { yyctx.lrdata->putTerm($1); }
             ;

newlines     : newlines NL
             | NL
             ;

op_newlines  : op_newlines NL
             |
             ;

%%

int yyerror(const char* s)
{
  fprintf(stderr, "yacc: %s\n", s);
  return 0;
}

void putKeyValue(const char* key, const char* value)
{ 
  yyctx.stdata->put(key, value);
  //printf("%s = %s\n", key, value);
}
