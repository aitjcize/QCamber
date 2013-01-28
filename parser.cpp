#include "parser.h"
#include "yyheader.h"
#include "db.tab.h"

#include <cstdio>
#include <iostream>
#include <utility>

using std::cout;
using std::endl;

extern struct yycontext yyctx;

int StructuredDataStore::dumpIndent = 0;

StructuredDataStore::StructuredDataStore()
{
  m_mode = KEY_VALUE;
  m_currentBlock = NULL;
}

void StructuredDataStore::put(string key, string value)
{
  switch (m_mode) {
  case KEY_VALUE:
    m_valueData[key] = value;
    break;
  case BLOCK:
    m_currentBlock->put(key, value);
    break;
  }
}

void StructuredDataStore::newElement(string name)
{
  if (m_currentBlock != NULL) { // nested block
    m_currentBlock->newElement(name);
  } else {
    m_mode = BLOCK;
    m_currentElementName = name;
    m_currentBlock = new StructuredDataStore;
  }
}

bool StructuredDataStore::commitElement(void)
{
  if (!m_currentBlock) {
    return false;
  }

  if (m_currentBlock != NULL) {
    if (!m_currentBlock->commitElement()) {
      m_mode = KEY_VALUE;
      m_blockData.insert(std::make_pair(m_currentElementName, m_currentBlock));
      m_currentBlock = NULL;
      return true;
    }
  }
  return true;
}

string StructuredDataStore::get(string key)
{
  if (m_valueData.find(key) != m_valueData.end()) {
    return m_valueData[key];
  }
  throw InvalidKeyException();
}

StructuredDataStore::BlockIterPair
StructuredDataStore::getBlocksByKey(string key)
{
  return m_blockData.equal_range(key);
}

void StructuredDataStore::dump(void)
{
  for (ValueType::const_iterator iter = m_valueData.begin();
      iter != m_valueData.end(); ++iter) {
    cout << string(dumpIndent * 2, ' ');
    cout << iter->first << " = " << iter->second << endl;
  }

  dumpIndent += 1;
  for (BlockType::const_iterator iter = m_blockData.begin();
      iter != m_blockData.end(); ++iter) {
    cout << string(dumpIndent * 2 - 2, ' ');
    cout << iter->first << " {" << endl;
    iter->second->dump();
    cout << string(dumpIndent * 2 - 2, ' ');
    cout << "}" << endl;
  }
  dumpIndent -= 1;
}

void LineRecordDataStore::putTerm(string term)
{
  m_currentElement.push_back(term);
}

void LineRecordDataStore::putLineRecord(void)
{
  m_data.push_back(m_currentElement);
  m_currentElement = ElementType();
}

void LineRecordDataStore::dump(void)
{
  cout << "=== LineRecordDataStore ===" << endl;
  for (DataType::const_iterator iter = m_data.begin();
      iter != m_data.end(); ++iter) {
    for (ElementType::const_iterator iter2 = iter->begin();
        iter2 != iter->end(); ++iter2) {
      cout << *iter2 << " ";
    }
    cout << endl;
  }
}

Parser::Parser(string filename, Type type)
{
  m_fileName = filename;
  m_type = type;
}
 
Parser::~Parser()
{
  
}

DataStore* Parser::parse(void)
{
  FILE* fin = freopen(m_fileName.c_str(), "r", stdin);
  if (fin == NULL) {
    fprintf(stderr, "can't open file `%s'\n", m_fileName.c_str());
  }

  yyctx.type = m_type;
  DataStore* data = NULL;

  switch (m_type) {
  case STRUCTURED:
    data = yyctx.stdata = new StructuredDataStore;
    break;
  case LINE_RECORD:
    data = yyctx.lrdata = new LineRecordDataStore;
    break;
  }

  yyparse();
  //data->dump();

  return data;
}
