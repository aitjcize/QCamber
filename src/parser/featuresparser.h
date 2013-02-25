#ifndef __FEATURES_PARSER_H__
#define __FEATURES_PARSER_H__

#include "parser.h"
#include "record.h"
#include "structuredtextparser.h"

#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>

class FeaturesDataStore: public DataStore {
public:
  virtual ~FeaturesDataStore();

  typedef QMap<int, QString> IDMapType;
  typedef QMap<int, int> CountMapType;

  void setJobName(const QString& name);
  void setStepName(const QString& name);
  void setLayerName(const QString& name);

  void putAttrlist(StructuredTextDataStore* ds);
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

  const CountMapType& posLineCountMap(void){return m_posLineCount;}
  const CountMapType& posPadCountMap(void){return m_posPadCount;}
  const CountMapType& posArcCountMap(void){return m_posArchCount;}
  const CountMapType& posSurfaceCountMap(void){return m_posSurfaceCount;}

  const CountMapType& negLineCountMap(void){return m_negLineCount;}
  const CountMapType& negPadCountMap(void){return m_negPadCount;}
  const CountMapType& negArcCountMap(void){return m_negArchCount;}
  const CountMapType& negSurfaceCountMap(void){return m_negSurfaceCount;}

  QString jobName(void);
  QString stepName(void);
  QString layerName(void);
  QString attrlist(QString name);

  const IDMapType& symbolNameMap(void);
  const IDMapType& attribNameMap(void);
  const IDMapType& attribTextMap(void);
  QList<Record*>& records(void);

  virtual void dump(void);

protected:
  QString stripAttr(const QString& line); 

private:
  QString m_jobName;
  QString m_stepName;
  QString m_layerName;

  QMap<QString, QString> m_attrlist;
  IDMapType m_symbolNameMap;
  IDMapType m_attribNameMap;
  IDMapType m_attribTextMap;

  CountMapType m_posLineCount;
  CountMapType m_posPadCount;
  CountMapType m_posArchCount;
  CountMapType m_posSurfaceCount;

  CountMapType m_negLineCount;
  CountMapType m_negPadCount;
  CountMapType m_negArchCount;
  CountMapType m_negSurfaceCount;

  QList<Record*> m_records;
  SurfaceRecord* m_currentSurface;
};

class FeaturesParser: public Parser {
public:
  FeaturesParser(const QString& filename);
  virtual ~FeaturesParser();
  
  virtual FeaturesDataStore* parse(void);
};

#endif /* __FEATURES_PARSER_H__ */
