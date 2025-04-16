/**
 * @file   featuresparser.cpp
 * @author Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 *
 * Copyright (C) 2012 - 2014 Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "featuresparser.h"

#include <map>
#include <string>

#include <QtCore>
#include <QtDebug>

#include "structuredtextparser.h"
#include "record.h"

FeaturesParser::FeaturesParser(const QString& filename):
  Parser(filename), m_ds(NULL)
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
  m_ds = ds;

  // layer feature related
  QRegularExpression rx("^.*/([^/]+)/steps/([^/]+)/layers/([^/]+)/features$");
  QRegularExpressionMatch m = rx.match(m_fileName);
  if (m.hasMatch()) {
    QStringList caps = m.capturedTexts();
    ds->setJobName(caps[1]);
    ds->setStepName(caps[2]);
    ds->setLayerName(caps[3]);

    // steps attribute
    QRegularExpression rp("(steps/[^/]+)/.*");
    QString stepAttrName = QString(m_fileName).replace(rp, "\\1/attrlist");
    StructuredTextParser sp(stepAttrName);
    StructuredTextDataStore* sds = sp.parse();
    putAttrlist(sds);
    delete sds;

    // layer attribute
    rp.setPattern("(layers/[^/]+)/.*");
    QString layerAttrName = QString(m_fileName).replace(rp, "\\1/attrlist");
    StructuredTextParser lp(layerAttrName);
    StructuredTextDataStore* lds = lp.parse();
    putAttrlist(lds);
    delete lds;
  }

  bool surface = false;

  while (!file.atEnd()) {
    QString line = file.readLine();
    line.chop(1); // remove newline character

    if (line.startsWith("#") || line.length() == 0) { // comment
      continue;
    }

    if (surface) {
      if (line.startsWith("SE")) {
        surface = false;
        parseSurfaceEnd();
      } else {
        parseSurfaceLineData(line);
      }
      continue;
    }

    if (line.startsWith("$")) { // symbol names
      parseSymbolName(line);
    } else if (line.startsWith("@")) { // attrib names
      parseAttribName(line);
    } else if (line.startsWith("&")) { // attrib text strings
      parseAttribText(line);
    } else if (line.startsWith("L")) { // line
      parseLine(line);
    } else if (line.startsWith("P")) { // pad
      parsePad(line);
    } else if (line.startsWith("A")) { // arc
      parseArc(line);
    } else if (line.startsWith("T")) { // text
      parseText(line);
    } else if (line.startsWith("B")) { // barcode
      parseBarcode(line);
    } else if (line.startsWith("S")) { // surface
      parseSurfaceStart(line);
      surface = true;
    }
  }
  return ds;
}

void FeaturesParser::putAttrlist(const StructuredTextDataStore* ds)
{
  if (!ds)
    return;
  const StructuredTextDataStore::ValueType d = ds->getValueData();
  for (StructuredTextDataStore::ValueType::const_iterator it = d.begin();
      it != d.end(); ++it) {
    m_ds->putAttrlistItem(QString::fromStdString(it->first),
        QString::fromStdString(it->second));
  }
}

void FeaturesParser::parseSymbolName(const QString& line)
{
  QStringList param = line.split(" ", Qt::SkipEmptyParts);
  if (param.length() == 2) {
    int id = param[0].right(param[0].length() - 1).toInt();
    m_ds->putSymbolName(id, param[1]);
  }
}

void FeaturesParser::parseAttribName(const QString& line)
{
  QStringList param = line.split(" ", Qt::SkipEmptyParts);
  if (param.length() == 2) {
    int id = param[0].right(param[0].length() - 1).toInt();
    m_ds->putAttribName(id, param[1]);
  }
}

void FeaturesParser::parseAttribText(const QString& line)
{
  QStringList param = line.split(" ", Qt::SkipEmptyParts);
  if (param.length() == 2) {
    int id = param[0].right(param[0].length() - 1).toInt();
    m_ds->putAttribText(id, param[1]);
  }
}

void FeaturesParser::parseLine(const QString& line)
{
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

  LineRecord* rec = new LineRecord(m_ds, param, attrib);
  m_ds->putLine(rec);
}

void FeaturesParser::parsePad(const QString& line)
{
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

  PadRecord* rec = new PadRecord(m_ds, param, attrib);
  m_ds->putPad(rec);
}

void FeaturesParser::parseArc(const QString& line)
{
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

  ArcRecord* rec = new ArcRecord(m_ds, param, attrib);
  m_ds->putArc(rec);
}

void FeaturesParser::parseText(const QString& line)
{
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

  TextRecord* rec = new TextRecord(m_ds, param, attrib);
  m_ds->putText(rec);
}

void FeaturesParser::parseBarcode(const QString& line)
{
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

  BarcodeRecord* rec = new BarcodeRecord(m_ds, param, attrib);
  m_ds->putBarcode(rec);
}

void FeaturesParser::parseSurfaceStart(const QString& line)
{
  QStringList param;
  AttribData attrib;
  parseAttributes(line, &param, &attrib);

  SurfaceRecord* rec = new SurfaceRecord(m_ds, param, attrib);
  m_currentSurface = rec;
  m_ds->putSurfaceRecord(rec);
}

void FeaturesParser::parseSurfaceLineData(const QString& line)
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

void FeaturesParser::parseSurfaceEnd()
{
  m_currentSurface = NULL;
}

void FeaturesParser::parseAttributes(const QString& line,
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
    *param = left.split(" ", Qt::SkipEmptyParts);
    *param << middle;
    *param += right.split(" ", Qt::SkipEmptyParts);
  } else {
    *param = record.split(" ", Qt::SkipEmptyParts);
  }

  if (!attr.isEmpty()) {
    QStringList terms = attr.split(',');
    for (int i = 0; i < terms.size(); ++i) {
      QStringList v = terms[i].split('=');
      QString key = m_ds->attribNameMap()[v[0].toInt()];
      if (v.size() == 1) {
        (*attrib)[key] = "true";
      } else {
        (*attrib)[key] = m_ds->attribTextMap()[v[1].toInt()];
      }
    }
  }
}
