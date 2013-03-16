delim       [ \t]
nl          [\n\r]
ws          {delim}+
pletter     [A-Za-z0-9_.\-+/&"':;]
mletter     [A-Za-z0-9_.\-+/&"':; ]
var         {pletter}{mletter}*{pletter}

%option noyywrap
%option yylineno

%{
#include "yyheader.h"

#include <stdio.h>
#include <string.h>
#include "db.tab.h"

extern YYSTYPE yylval;

%}

%%

"{"        { return *yytext; }
"}"        { return *yytext; }
"="        { return *yytext; }
{pletter}  { yylval = strdup(yytext); return VAR; }
{var}      { yylval = strdup(yytext); return VAR; }
{nl}       { return NL; }
{ws}       { }

%%
