delim       [ \t]
nl          [\n\r]
ws          {delim}+
letter      [A-Za-z0-9_.\-+]
var         {letter}+

%{
#include "yyheader.h"

#include <stdio.h>
#include <string.h>
#include "kvt.tab.h"

extern YYSTYPE yylval;

%}

%%

"{"      { return *yytext; }
"}"      { return *yytext; }
"="      { return *yytext; }
{var}    { yylval = strdup(yytext); return VAR; }
{nl}     { return NL; }
{ws}     { }

%%
