#ifndef __YY_HEADER_H__
#define __YY_HEADER_H__

#define YYSTYPE char*

#include "parser.h"

struct yycontext {
  Parser::Type type;
  KeyValueDataStore* kvdata;
  ArrayDataStore* ardata;
  LineRecordDataStore* lrdata;
};

#endif /* __YY_HEADER_H__ */
