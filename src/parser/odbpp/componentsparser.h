#ifndef __COMPONENTS_PARSER_H__
#define __COMPONENTS_PARSER_H__

#include "parser.h"
#include "componentsdatastore.h"

class ComponentsParser : public Parser {
public:
  ComponentsParser(const QString& filename);
  virtual ~ComponentsParser();

  virtual ComponentsDataStore* parse(void);
};

#endif /* __COMPONENTS_PARSER_H__ */
