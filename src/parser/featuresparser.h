#ifndef __FEATURES_PARSER_H__
#define __FEATURES_PARSER_H__

#include "parser.h"
#include "record.h"

#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>

class FeaturesDataStore: public DataStore {
public:
  typedef QMap<int, QString> IDMapType;

  void putSymbolName(const QString& line);
  void putAttribName(const QString& line);
  void putAttribText(const QString& line);
  void putLine(const QString& line);
  void putPad(const QString& line);
  void putArc(const QString& line);
  void putText(const QString& line);
  void putBarcode(const QString& line);
  void surfaceStart(const QString& line);
  void surfaceLineData(const QString& line);
  void surfaceEnd(void);

  QList<Record*>& records(void);

  virtual void dump(void);

protected:
  QString stripAttr(const QString& line); 

private:
  IDMapType m_symbolNameMap;
  IDMapType m_attribNameMap;
  IDMapType m_attribTextMap;

  QList<Record*> m_records;
  SurfaceRecord* m_currentSurface;
};

class FeaturesParser: public Parser {
public:
  FeaturesParser(const char* filename);
  FeaturesParser(QString filename);
  virtual ~FeaturesParser();
  
  virtual FeaturesDataStore* parse(void);
};

#endif /* __FEATURES_PARSER_H__ */
