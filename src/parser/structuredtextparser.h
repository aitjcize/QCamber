#ifndef __STRUCTURED_TEXT_PARSER_H__
#define __STRUCTURED_TEXT_PARSER_H__

#include "parser.h"

#include <string>

using std::string;

class StructuredTextDataStore: public DataStore {
public:
  class InvalidKeyException: public std::exception {
  };

  typedef enum { KEY_VALUE = 0, BLOCK } PutMode;

  typedef map<string, string> ValueType;
  typedef multimap<string, StructuredTextDataStore*> BlockType;
  typedef BlockType::iterator BlockIter;
  typedef pair<BlockIter, BlockIter> BlockIterPair;

  StructuredTextDataStore();
  void newElement(string name);
  bool commitElement(void);

  string get(string key);
  BlockIterPair getBlocksByKey(string key);

  void put(string key, string value);
  virtual void dump(void);

  static int dumpIndent;

private:
  PutMode m_mode;
  ValueType m_valueData;
  BlockType m_blockData;
  StructuredTextDataStore* m_currentBlock;
  string m_currentElementName;
};

class StructuredTextParser : public Parser{
public:
  StructuredTextParser(const QString& filename);
  virtual ~StructuredTextParser();

  virtual StructuredTextDataStore* parse(void);
};

#endif /* __STRUCTURED_TEXT_PARSER_H__ */
