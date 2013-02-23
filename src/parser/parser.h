#ifndef __PARSER_H__
#define __PARSER_H__

#include <map>
#include <stdexcept>
#include <vector>

#include <QString>

using std::map;
using std::multimap;
using std::pair;
using std::vector;

class DataStore {
public:
  virtual ~DataStore() {}
  virtual void dump(void) = 0;
};

class Parser {
public:
  Parser(const QString& filename);
  virtual ~Parser();

  virtual DataStore* parse(void) = 0;

protected:
  QString m_fileName;
};

#endif /* __PARSER_H__ */
