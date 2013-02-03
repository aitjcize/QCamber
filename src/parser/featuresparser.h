#ifndef __FEATURES_PARSER_H__
#define __FEATURES_PARSER_H__

#include "parser.h"

#include <QMap>
#include <QString>
#include <QStringList>

class FeaturesDataStore: public DataStore {
public:
  typedef QMap<int, QString> IDMapType;
  void putSymbolName(const QString& line);
  void putAttribName(const QString& line);
  void putAttribText(const QString& line);

  virtual void dump(void);

private:
  IDMapType m_symbolNameMap;
  IDMapType m_attribNameMap;
  IDMapType m_attribTextMap;
};

class FeaturesParser: public Parser {
public:
  FeaturesParser(const char* filename);
  FeaturesParser(QString filename);
  virtual ~FeaturesParser();
  
  virtual FeaturesDataStore* parse(void);
};

#endif /* __FEATURES_PARSER_H__ */
