#ifndef __PARSER_H__
#define __PARSER_H__

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <QString>

using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::vector;

class DataStore {
public:
  virtual void dump(void) = 0;
};

class Parser {
public:
  Parser(QString filename);
  Parser(const char* filename);
  ~Parser();
  virtual DataStore* parse(void) = 0;

protected:
  string m_fileName;
};

#endif /* __PARSER_H__ */
