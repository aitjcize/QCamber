%{
#include "yyheader.h"
#include <stdio.h>

#include "parser.h"

struct yycontext yyctx;

extern int yyparse (void);

void putKeyValue(const char* key, const char* value);
int yyerror(const char* s);
int yylex(void);
%}

%token VAR
%token NL

%%

syntax       : op_newlines structures
             ;

structures   : structures structure
             | structure
             ;

structure    : VAR { yyctx.stds->newElement($1); }
               '{' op_newlines structures '}' newlines   {
                 yyctx.stds->commitElement();
              }
             | assignment
             ;

assignment   : VAR '=' VAR newlines { putKeyValue($1, $3); }
             | VAR '=' newlines     { putKeyValue($1, ""); }
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
  yyctx.stds->put(key, value);
  //printf("%s = %s\n", key, value);
}
