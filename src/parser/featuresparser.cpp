#include "featuresparser.h"

#include <map>
#include <string>

#include <QtCore>
#include <QtDebug>

FeaturesDataStore::FeaturesDataStore():
  m_posSurfaceCount(0), m_posTextCount(0), m_negSurfaceCount(0),
  m_negTextCount(0)
{
}

FeaturesDataStore::~FeaturesDataStore()
{
  for (int i = 0; i < m_records.size(); ++i) {
    delete m_records[i];
  }
}

void FeaturesDataStore::setJobName(const QString& name)
{
  m_jobName = name.toUpper();
}

void FeaturesDataStore::setStepName(const QString& name)
{
  m_stepName = name.toUpper();
}

void FeaturesDataStore::setLayerName(const QString& name)
{
  m_layerName = name.toUpper();
}

void FeaturesDataStore::putAttrlist(StructuredTextDataStore* ds)
{
  const StructuredTextDataStore::ValueType d = ds->getValueData();
  for (StructuredTextDataStore::ValueType::const_iterator it = d.begin();
      it != d.end(); ++it) {
    m_attrlist[QString::fromStdString(it->first)] =
      QString::fromStdString(it->second);
  }
}

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
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

  LineRecord* rec = new LineRecord(this, param, attrib);
  m_records.append(rec);

  if (rec->polarity == P) {
    ++m_posLineCountMap[rec->sym_num];
  } else {
    ++m_negLineCountMap[rec->sym_num];
  }
}

void FeaturesDataStore::putPad(const QString& line)
{
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

  PadRecord* rec = new PadRecord(this, param, attrib);
  m_records.append(rec);

  if (rec->polarity == P) {
    ++m_posPadCountMap[rec->sym_num];
  } else {
    ++m_negPadCountMap[rec->sym_num];
  }
}

void FeaturesDataStore::putArc(const QString& line)
{
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

  ArcRecord* rec = new ArcRecord(this, param, attrib);
  m_records.append(rec);

  if (rec->polarity == P) {
    ++m_posArcCountMap[rec->sym_num];
  } else {
    ++m_negArcCountMap[rec->sym_num];
  }
}

void FeaturesDataStore::putText(const QString& line)
{
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

  TextRecord* rec = new TextRecord(this, param, attrib);
  m_records.append(rec);

  if (rec->polarity == P) {
    ++m_posTextCount;
  } else {
    ++m_negTextCount;
  }
}

void FeaturesDataStore::putBarcode(const QString& line)
{
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

  m_records.append(new BarcodeRecord(this, param, attrib));
}

void FeaturesDataStore::surfaceStart(const QString& line)
{
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

  SurfaceRecord* rec = new SurfaceRecord(this, param, attrib);
  m_records.append(rec);
  m_currentSurface = rec;

  if (rec->polarity == P) {
    ++m_posSurfaceCount;
  } else {
    ++m_negSurfaceCount;
  }
}

void FeaturesDataStore::surfaceLineData(const QString& line)
{
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

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
  m_currentSurface = NULL;
}

void FeaturesDataStore::parseAttributes(const QString& line,
    QStringList* param, AttribData* attrib)
{
  int loc = line.lastIndexOf(";");
  QString record = line.left(loc).trimmed();
  QString attr;
  if (loc != -1) {
    attr = line.right(line.length() - loc - 1).trimmed();
  }

  if (record.indexOf("'") != -1) {
    int loc = record.indexOf("'");
    int loc2 = record.indexOf("'", loc + 1);
    QString left = record.left(loc);
    QString middle = record.mid(loc + 1, loc2 - loc - 1);
    QString right = record.right(record.length() - loc2 - 1);
    *param = left.split(" ", QString::SkipEmptyParts);
    *param << middle;
    *param += right.split(" ", QString::SkipEmptyParts);
  } else {
    *param = record.split(" ", QString::SkipEmptyParts);
  }

  if (!attr.isEmpty()) {
    QStringList terms = attr.split(',');
    for (int i = 0; i < terms.size(); ++i) {
      QStringList v = terms[i].split('=');
      QString key = m_attribNameMap[v[0].toInt()];
      if (v.size() == 1) {
        (*attrib)[key] = "true";
      } else {
        (*attrib)[key] = m_attribTextMap[v[1].toInt()];
      }
    }
  }
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
  QFile file(m_fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug("parse: can't open `%s' for reading", qPrintable(m_fileName));
    return NULL;
  }

  FeaturesDataStore* ds = new FeaturesDataStore;
  // layer feature related
  QRegExp rx(".*/([^/]+)/steps/([^/]+)/layers/([^/]+)/features");
  if (rx.exactMatch(m_fileName)) {
    QStringList caps = rx.capturedTexts();
    ds->setJobName(caps[1]);
    ds->setStepName(caps[2]);
    ds->setLayerName(caps[3]);

    // steps attribute
    QRegExp rp("(steps/[^/]+)/.*");
    QString stepAttrName = QString(m_fileName).replace(rp, "\\1/attrlist");
    StructuredTextParser sp(stepAttrName);
    StructuredTextDataStore* sds = sp.parse();
    ds->putAttrlist(sds);
    delete sds;

    // layer attribute
    rp.setPattern("(layers/[^/]+)/.*");
    QString layerAttrName = QString(m_fileName).replace(rp, "\\1/attrlist");
    StructuredTextParser lp(layerAttrName);
    StructuredTextDataStore* lds = lp.parse();
    ds->putAttrlist(lds);
    delete lds;
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
