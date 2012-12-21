#include "parser.h"
#include <cstdio>

extern int yydebug;

int main(int argc, const char *argv[])
{
  yydebug = 0;
  Parser parser("matrix", Parser::ARRAY);
  parser.parse();
  return 0;
}
