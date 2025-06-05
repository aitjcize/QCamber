#ifndef __PACKAGE_PARSER_H__
#define __PACKAGE_PARSER_H__

#include "parser.h"
#include "packagedatastore.h"

class PackageParser : public Parser {
public:
  PackageParser(const QString& filename);
  virtual ~PackageParser();

  virtual PackageDataStore* parse(void);
};

#endif /* __PACKAGE_PARSER_H__ */
