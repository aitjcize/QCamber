#include "parser.h"
#include <iostream>

using std::cout;
using std::endl;

extern int yydebug;

int main(int argc, const char *argv[])
{
  yydebug = 0;
  Parser parser("kv", Parser::KEY_VALUE);
  parser.parse();
  return 0;
}
