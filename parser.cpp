#include "parser.h"
#include "yyheader.h"

#include <cstdio>
#include <iostream>

using std::cout;
using std::endl;

extern struct yycontext yyctx;

string KeyValueDataStore::get(const char* key)
{
  return data[key];
}

string KeyValueDataStore::get(const string& key)
{
  return get(key.c_str());
}

void KeyValueDataStore::put(string key, string value)
{
  data[key] = value;
}

void KeyValueDataStore::dump(void)
{
  cout << "=== KeyValueDataStore ===" << endl;
  for (DataType::const_iterator iter = data.begin();
      iter != data.end(); ++iter) {
    cout << iter->first << " = " << iter->second << endl;
  }
}

void ArrayDataStore::putKeyValue(string key, string value)
{
  currentElement[key] = value;
}

void ArrayDataStore::putElement(string array)
{
  data[array].push_back(currentElement);
  currentElement = ElementType();
}

void ArrayDataStore::dump(void)
{
  cout << "=== ArrayDataStore ===" << endl;
  for (DataType::const_iterator iter = data.begin();
      iter != data.end(); ++iter) {
    cout << iter->first << " {" << endl;
    for (vector<ElementType>::const_iterator iter2 = iter->second.begin();
        iter2 != iter->second.end(); ++iter2) {
      cout << "--" << endl;
      for (ElementType::const_iterator iter3 = iter2->begin();
          iter3 != iter2->end(); ++iter3) {
        cout << "\t" << iter3->first << " = " << iter3->second << endl;
      }
    }
    cout << "}" << endl;
  }
}

void LineRecordDataStore::putTerm(string term)
{
  currentElement.push_back(term);
}

void LineRecordDataStore::putLineRecord(void)
{
  data.push_back(currentElement);
  currentElement = ElementType();
}

void LineRecordDataStore::dump(void)
{
  cout << "=== LineRecordDataStore ===" << endl;
  for (DataType::const_iterator iter = data.begin();
      iter != data.end(); ++iter) {
    for (ElementType::const_iterator iter2 = iter->begin();
        iter2 != iter->end(); ++iter2) {
      cout << *iter2 << " ";
    }
    cout << endl;
  }
}

Parser::Parser(const char* filename, Type type)
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
  DataStore* data;

  switch (m_type) {
  case KEY_VALUE:
    data = yyctx.kvdata = new KeyValueDataStore;
    break;
  case ARRAY:
    data = yyctx.ardata = new ArrayDataStore;
    break;
  case LINE_RECORD:
    data = yyctx.lrdata = new LineRecordDataStore;
    break;
  }

  yyparse();
  data->dump();

  return data;
}
