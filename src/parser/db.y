/**
 * @file   db.y
 * @author Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 *
 * Copyright (C) 2012 - 2014 Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

%{
#include "yyheader.h"
#include <stdio.h>

#include "parser.h"

struct yycontext yyctx;

extern int yyparse(void);
extern int yylineno;

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
  fprintf(stderr, "yacc: %d: %s\n", yylineno, s);
  return 0;
}

void putKeyValue(const char* key, const char* value)
{
  yyctx.stds->put(key, value);
  //printf("%s = %s\n", key, value);
}
