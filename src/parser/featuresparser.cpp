#include "featuresparser.h"

#include <QtCore>
#define _DOUBLE_SLASHES_ "__DOUBLE_SLASHES_DARK_FLAME_MASTER__"
void FeaturesDataStore::putSymbolName(const QString& line)
{
  QStringList param = line.split(" ");
  if (param.length() == 2) {
    int id = param[0].right(param[0].length() - 1).toInt();
    m_symbolNameMap[id] = param[1];
  }
}

void FeaturesDataStore::putAttribName(const QString& line)
{
  QStringList param = line.split(" ");
  if (param.length() == 2) {
    int id = param[0].right(param[0].length() - 1).toInt();
    m_attribNameMap[id] = param[1];
  }
}

void FeaturesDataStore::putAttribText(const QString& line)
{
  QStringList param = line.split(" ");
  if (param.length() == 2) {
    int id = param[0].right(param[0].length() - 1).toInt();
    m_attribTextMap[id] = param[1];
  }
}

void FeaturesDataStore::putLine(const QString& line)
{
  QStringList param = stripAttr(line).split(" ");
  LineRecord* rec = new LineRecord;
  int i = 0;
  rec->ds = this;
  rec->xs = param[++i].toDouble();
  rec->ys = param[++i].toDouble();
  rec->xe = param[++i].toDouble();
  rec->ye = param[++i].toDouble();
  rec->sym_num = param[++i].toInt();
  rec->polarity = (param[++i] == "P")? P: N;
  rec->dcode = param[++i].toInt();
  m_records.append(rec);
}

void FeaturesDataStore::putPad(const QString& line)
{
  QStringList param = stripAttr(line).split(" ");
  PadRecord* rec = new PadRecord;
  int i = 0;
  rec->ds = this;
  rec->x = param[++i].toDouble();
  rec->y = param[++i].toDouble();
  rec->sym_num = param[++i].toInt();
  rec->polarity = (param[++i] == "P")? P: N;
  rec->dcode = param[++i].toInt();
  rec->orient = (Orient)param[++i].toInt();
  m_records.append(rec);
}

void FeaturesDataStore::putArc(const QString& line)
{
  QStringList param = stripAttr(line).split(" ");
  ArcRecord* rec = new ArcRecord;
  int i = 0;
  rec->ds = this;
  rec->xs = param[++i].toDouble();
  rec->ys = param[++i].toDouble();
  rec->xe = param[++i].toDouble();
  rec->ye = param[++i].toDouble();
  rec->xc = param[++i].toDouble();
  rec->yc = param[++i].toDouble();
  rec->sym_num = param[++i].toInt();
  rec->polarity = (param[++i] == "P")? P: N;
  rec->dcode = param[++i].toInt();
  rec->cw = (param[++i] == "Y");
  m_records.append(rec);
}

void FeaturesDataStore::putText(const QString& line)
{
  QStringList param = stripAttr(line).split(" ");
  TextRecord* rec = new TextRecord;
  int i = 0;
  rec->ds = this;
  rec->x = param[++i].toDouble();
  rec->y = param[++i].toDouble();
  rec->font = param[++i];
  rec->polarity = (param[++i] == "P")? P: N;
  rec->orient = (Orient)param[++i].toInt();
  rec->xsize = param[++i].toDouble();
  rec->ysize = param[++i].toDouble();
  rec->width_factor = param[++i].toDouble();
  rec->text = "";
  int ends = -1;
  while(ends!=1){
    QString str(param[++i]);
    if(!ends)
      rec->text += " ";
    else
      str.replace(QRegExp("^'"), "");
    str.replace("\\\\", _DOUBLE_SLASHES_);
    if(str.endsWith("\\'"))
        ends = 0;
    else if (str.endsWith("'"))
        ends = 1;
    else
        ends = 0;
    if(ends)
        str.replace(QRegExp("'$"), "");
    str.replace("\\'", "'");
    str.replace(_DOUBLE_SLASHES_, "\\");
    rec->text += str;
  };

  rec->version = param[++i].toInt();
  m_records.append(rec);
}

void FeaturesDataStore::putBarcode(const QString& line)
{
  QStringList param = stripAttr(line).split(" ");
  BarcodeRecord* rec = new BarcodeRecord;
  int i = 0;
  rec->ds = this;
  rec->x = param[++i].toDouble();
  rec->y = param[++i].toDouble();
  rec->barcode = param[++i];
  rec->font = param[++i];
  rec->polarity = (param[++i] == "P")? P: N;
  rec->orient = (Orient)param[++i].toInt();
  rec->e = param[++i];
  rec->w = param[++i].toDouble();
  rec->h = param[++i].toDouble();
  rec->fasc = (param[++i] == "Y");
  rec->cs = (param[++i] == "Y");
  rec->bg = (param[++i] == "Y");
  rec->astr = (param[++i] == "Y");
  rec->astr_pos = (param[++i] == "T")? BarcodeRecord::T : BarcodeRecord::B;
  rec->text = "";
  int ends = -1;
  while(ends!=1){
    QString str(param[++i]);
    if(!ends)
      rec->text += " ";
    else
      str.replace(QRegExp("^'"), "");
    str.replace("\\\\", _DOUBLE_SLASHES_);
    if(str.endsWith("\\'"))
        ends = 0;
    else if (str.endsWith("'"))
        ends = 1;
    else
        ends = 0;
    if(ends)
        str.replace(QRegExp("'$"), "");
    str.replace("\\'", "'");
    str.replace(_DOUBLE_SLASHES_, "\\");
    rec->text += str;
  };

  m_records.append(rec);
}

void FeaturesDataStore::surfaceStart(const QString& line)
{
  QStringList param = stripAttr(line).split(" ");
  SurfaceRecord* rec = new SurfaceRecord;
  int i = 0;
  rec->ds = this;
  rec->polarity = (param[++i] == "P")? P: N;
  rec->dcode = param[++i].toInt();
  m_records.append(rec);
  m_currentSurface = rec;
}

void FeaturesDataStore::surfaceLineData(const QString& line)
{
  QStringList param = stripAttr(line).split(" ");
  int i = 0;
  if (line.startsWith("OB")) {
    PolygonRecord* rec = new PolygonRecord;
    rec->ds = this;
    rec->xbs = param[++i].toDouble();
    rec->ybs = param[++i].toDouble();
    rec->poly_type = (param[++i] == "I")? PolygonRecord::I : PolygonRecord::H;
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

FeaturesParser::FeaturesParser(const char* filename): Parser(filename)
{
}

FeaturesParser::FeaturesParser(QString filename): Parser(filename)
{
}

FeaturesParser::~FeaturesParser()
{
  
}

FeaturesDataStore* FeaturesParser::parse(void)
{
  FeaturesDataStore* ds = new FeaturesDataStore;
  QFile file(m_fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return NULL;

  bool surface = false;

  while (!file.atEnd()) {
    QString line = file.readLine();
    line.chop(1); // remove newline character

    if (line.startsWith("#")) { // comment
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
