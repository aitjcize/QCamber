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
  FeaturesDataStore();
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

  QString jobName(void) const { return m_jobName; }
  QString stepName(void) const { return m_stepName; }
  QString layerName(void) const { return m_layerName; }
  QString attrlist(QString name) { return m_attrlist[name]; }

  const IDMapType& symbolNameMap(void) const { return m_symbolNameMap; }
  const IDMapType& attribNameMap(void) const { return m_attribNameMap; }
  const IDMapType& attribTextMap(void) const { return m_attribTextMap; }
  const QList<Record*> records(void) const { return m_records; }

  const CountMapType& posLineCountMap(void) const { return m_posLineCountMap; }
  const CountMapType& posPadCountMap(void) const { return m_posPadCountMap; }
  const CountMapType& posArcCountMap(void) const { return m_posArcCountMap; }
  int posSurfaceCount(void) const { return m_posSurfaceCount; }
  int posTextCount(void) const { return m_posTextCount; }
  int posBarcodeCount(void) const { return m_posBarcodeCount; }

  const CountMapType& negLineCountMap(void) const { return m_negLineCountMap; }
  const CountMapType& negPadCountMap(void) const { return m_negPadCountMap; }
  const CountMapType& negArcCountMap(void) const { return m_negArcCountMap; }
  int negSurfaceCount(void) const { return m_negSurfaceCount; }
  int negTextCount(void) const { return m_negTextCount; }
  int negBarcodeCount(void) const { return m_negBarcodeCount; }

  virtual void dump(void);

protected:
  void parseAttributes(const QString& line, QStringList* param,
      AttribData* attrib);

private:
  QString m_jobName;
  QString m_stepName;
  QString m_layerName;

  QMap<QString, QString> m_attrlist;
  IDMapType m_symbolNameMap;
  IDMapType m_attribNameMap;
  IDMapType m_attribTextMap;

  CountMapType m_posLineCountMap;
  CountMapType m_posPadCountMap;
  CountMapType m_posArcCountMap;
  int m_posSurfaceCount;
  int m_posTextCount;
  int m_posBarcodeCount;

  CountMapType m_negLineCountMap;
  CountMapType m_negPadCountMap;
  CountMapType m_negArcCountMap;
  int m_negSurfaceCount;
  int m_negTextCount;
  int m_negBarcodeCount;

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
