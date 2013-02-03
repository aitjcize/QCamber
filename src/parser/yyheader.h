#ifndef __YY_HEADER_H__
#define __YY_HEADER_H__

#define YYSTYPE char*

#include "structuredtextparser.h"

struct yycontext {
  StructuredTextDataStore* stds;
};

#endif /* __YY_HEADER_H__ */
