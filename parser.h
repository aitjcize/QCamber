#ifndef __PARSER_H__
#define __PARSER_H__

#include <map>
#include <string>
#include <vector>

using std::map;
using std::multimap;
using std::string;
using std::vector;

class DataStore {
public:
  virtual void dump(void) = 0;
};

class StructuredDataStore: public DataStore {
public:
  typedef enum { KEY_VALUE = 0, BLOCK } PutMode;

  typedef map<string, string> KeyValueType;
  typedef multimap<string, StructuredDataStore*> KeyBlockType;

  StructuredDataStore();
  void newElement(string name);
  bool commitElement(void);

  void put(string key, string value);
  virtual void dump(void);

  static int dumpIndent;

private:
  PutMode m_mode;
  KeyValueType m_keyValueData;
  KeyBlockType m_blockData;
  StructuredDataStore* m_currentBlock;
  string m_currentElementName;
};

class LineRecordDataStore: public DataStore {
public:
  typedef vector<string> ElementType;
  typedef vector<ElementType> DataType;

  void putTerm(string term);
  void putLineRecord(void);
  virtual void dump(void);

private:
  DataType m_data;
  ElementType m_currentElement;
};

class Parser {
public:
  typedef enum {
    STRUCTURED = 0,
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
