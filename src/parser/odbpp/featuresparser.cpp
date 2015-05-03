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
#include "structuredtextparser.h"

#include <map>
#include <string>

#include <QtCore>
#include <QtDebug>

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
