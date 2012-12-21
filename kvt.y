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

syntax       : op_newlines arrays
             | op_newlines linerecords
             | op_newlines assignments
             ;

arrays	     : arrays array
             | array
             ;

array        : VAR '{' newlines assignments '}' newlines   {
                 yyctx.ardata->putElement($1);
              }
             ;

assignments  : assignments assignment
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
}

void putKeyValue(const char* key, const char* value)
{ 
  switch (yyctx.type) {
  case Parser::KEY_VALUE:
    yyctx.kvdata->put(key, value);
    break;
  case Parser::ARRAY:
    yyctx.ardata->putKeyValue(key, value);
    break;
  default:
    yyerror("invalid type in putKeyValue");
  }
  //printf("%s = %s\n", key, value);
}
