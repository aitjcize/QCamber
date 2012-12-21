#ifndef __PARSER_H__
#define __PARSER_H__

#include "kvt.tab.h"

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

class DataStore {
public:
  virtual void dump(void) = 0;
};

class KeyValueDataStore: public DataStore {
public:
  typedef map<string, string> DataType;

  string get(const char* key);
  string get(const string& key);

  void put(string key, string value);
  virtual void dump(void);

private:
  DataType data;
};

class ArrayDataStore: public DataStore {
public:
  typedef map<string, string> ElementType;
  typedef map<string, vector<ElementType> > DataType;

  void putKeyValue(string key, string value);
  void putElement(string array);
  virtual void dump(void);

private:
  DataType data;
  ElementType currentElement;
};

class LineRecordDataStore: public DataStore {
public:
  typedef vector<string> ElementType;
  typedef vector<ElementType> DataType;

  void putTerm(string term);
  void putLineRecord(void);
  virtual void dump(void);

private:
  DataType data;
  ElementType currentElement;
};

class Parser {
public:
  typedef enum {
    KEY_VALUE = 0,
    ARRAY,
    LINE_RECORD,
  } Type;

  Parser(const char* filename, Type type);
  ~Parser();
  virtual DataStore* parse(void);

private:
  string m_fileName;
  Type m_type;
};

#endif /* __PARSER_H__ */
