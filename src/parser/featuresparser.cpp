#include "featuresparser.h"

#include <QtCore>

void FeaturesDataStore::putSymbolName(const QString& line)
{
  QStringList param = line.split(" ", QString::SkipEmptyParts);
  if (param.length() == 2) {
    int id = param[0].right(param[0].length() - 1).toInt();
    m_symbolNameMap[id] = param[1];
  }
}

void FeaturesDataStore::putAttribName(const QString& line)
{
  QStringList param = line.split(" ", QString::SkipEmptyParts);
  if (param.length() == 2) {
    int id = param[0].right(param[0].length() - 1).toInt();
    m_attribNameMap[id] = param[1];
  }
}

void FeaturesDataStore::putAttribText(const QString& line)
{
  QStringList param = line.split(" ", QString::SkipEmptyParts);
  if (param.length() == 2) {
    int id = param[0].right(param[0].length() - 1).toInt();
    m_attribTextMap[id] = param[1];
  }
}

void FeaturesDataStore::putLine(const QString& line)
{
  QStringList param = stripAttr(line).split(" ", QString::SkipEmptyParts);
  m_records.append(new LineRecord(this, param));
}

void FeaturesDataStore::putPad(const QString& line)
{
  QStringList param = stripAttr(line).split(" ", QString::SkipEmptyParts);
  m_records.append(new PadRecord(this, param));
}

void FeaturesDataStore::putArc(const QString& line)
{
  QStringList param = stripAttr(line).split(" ", QString::SkipEmptyParts);
  m_records.append(new ArcRecord(this, param));
}

void FeaturesDataStore::putText(const QString& line)
{
  int loc, loc2;
  QString l = stripAttr(line);
  loc = l.indexOf("'");
  loc2 = l.indexOf("'", loc + 1);
  QString left = l.left(loc);
  QString middle = l.mid(loc + 1, loc2 - loc - 1);
  QString right = l.right(l.length() - loc2 - 1);
  QStringList param = left.split(" ", QString::SkipEmptyParts);
  param << middle;
  param += right.split(" ", QString::SkipEmptyParts);
  m_records.append(new TextRecord(this, param));
}

void FeaturesDataStore::putBarcode(const QString& line)
{
  int loc, loc2;
  QString l = stripAttr(line);
  loc = l.indexOf("'");
  loc2 = l.indexOf("'", loc + 1);
  QString left = l.left(loc);
  QString middle = l.mid(loc + 1, loc2 - loc - 1);
  QString right = l.right(l.length() - loc2 - 1);
  QStringList param = left.split(" ", QString::SkipEmptyParts);
  param << middle;
  param += right.split(" ", QString::SkipEmptyParts);
  m_records.append(new BarcodeRecord(this, param));
}

void FeaturesDataStore::surfaceStart(const QString& line)
{
  QStringList param = stripAttr(line).split(" ", QString::SkipEmptyParts);
  SurfaceRecord* rec = new SurfaceRecord(this, param);
  m_records.append(rec);
  m_currentSurface = rec;
}

void FeaturesDataStore::surfaceLineData(const QString& line)
{
  QStringList param = stripAttr(line).split(" ", QString::SkipEmptyParts);
  if (line.startsWith("OB")) {
    PolygonRecord* rec = new PolygonRecord(param);
    m_currentSurface->polygons.append(rec);
    m_currentSurface->currentRecord = rec;
  } else if (line.startsWith("OS")) {
    SurfaceOperation* op = new SurfaceOperation;
    int i = 0;
    op->type = SurfaceOperation::SEGMENT;
    op->x = param[++i].toDouble();
    op->y = param[++i].toDouble();
    m_currentSurface->currentRecord->operations.append(op);
  } else if (line.startsWith("OC")) {
    SurfaceOperation* op = new SurfaceOperation;
    int i = 0;
    op->type = SurfaceOperation::CURVE;
    op->xe = param[++i].toDouble();
    op->ye = param[++i].toDouble();
    op->xc = param[++i].toDouble();
    op->yc = param[++i].toDouble();
    op->cw = (param[++i] == "Y");
    m_currentSurface->currentRecord->operations.append(op);
  } else if (line.startsWith("OE")) {
    m_currentSurface->currentRecord = NULL;
  }
}

void FeaturesDataStore::surfaceEnd(void)
{
  m_currentSurface->initSymbol();
  m_currentSurface = NULL;
}

QList<Record*>& FeaturesDataStore::records(void)
{
  return m_records;
}

const FeaturesDataStore::IDMapType& FeaturesDataStore::symbolNameMap(void)
{
  return m_symbolNameMap;
}

const FeaturesDataStore::IDMapType& FeaturesDataStore::attribNameMap(void)
{
  return m_attribNameMap;
}

const FeaturesDataStore::IDMapType& FeaturesDataStore::attribTextMap(void)
{
  return m_attribTextMap;
}

QString FeaturesDataStore::stripAttr(const QString& line)
{
  int loc = line.indexOf(";");
  return line.left(loc).trimmed();
}

void FeaturesDataStore::dump(void)
{
  qDebug() << "=== Symbol names ===";
  for (IDMapType::iterator it = m_symbolNameMap.begin();
      it != m_symbolNameMap.end(); ++it) {
    qDebug() << it.key() << it.value();
  }
  qDebug();

  qDebug() << "=== Attrib names ===";
  for (IDMapType::iterator it = m_attribNameMap.begin();
      it != m_attribNameMap.end(); ++it) {
    qDebug() << it.key() << it.value();
  }
  qDebug();

  qDebug() << "=== Attrib text ===";
  for (IDMapType::iterator it = m_attribTextMap.begin();
      it != m_attribTextMap.end(); ++it) {
    qDebug() << it.key() << it.value();
  }
}

FeaturesParser::FeaturesParser(const QString& filename): Parser(filename)
{
}

FeaturesParser::~FeaturesParser()
{
}

FeaturesDataStore* FeaturesParser::parse(void)
{
  FeaturesDataStore* ds = new FeaturesDataStore;
  QFile file(m_fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug("parse: can't open `%s' for reading", qPrintable(m_fileName));
    return NULL;
  }

  bool surface = false;

  while (!file.atEnd()) {
    QString line = file.readLine();
    line.chop(1); // remove newline character

    if (line.startsWith("#") && line.length() == 0) { // comment
      continue;
    }

    if (surface) {
      if (line.startsWith("SE")) {
        surface = false;
        ds->surfaceEnd();
      } else {
        ds->surfaceLineData(line);
      }
      continue;
    }
    
    if (line.startsWith("$")) { // symbol names
      ds->putSymbolName(line);
    } else if (line.startsWith("@")) { // attrib names
      ds->putAttribName(line);
    } else if (line.startsWith("&")) { // attrib text strings
      ds->putAttribText(line);
    } else if (line.startsWith("L")) { // line
      ds->putLine(line);
    } else if (line.startsWith("P")) { // pad
      ds->putPad(line);
    } else if (line.startsWith("A")) { // arc
      ds->putArc(line);
    } else if (line.startsWith("T")) { // text
      ds->putText(line);
    } else if (line.startsWith("B")) { // barcode
      ds->putBarcode(line);
    } else if (line.startsWith("S")) { // surface
      ds->surfaceStart(line);
      surface = true;
    }
  }
  return ds;
}
