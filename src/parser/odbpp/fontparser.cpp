/**
 * @file   fontparser.cpp
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

#include "fontparser.h"

#include <QDebug>
#include <QFile>

FontParser::FontParser(const QString& filename): Parser(filename)
{
}

FontParser::~FontParser()
{
}

FontDataStore* FontParser::parse(void)
{
  FontDataStore* ds = new FontDataStore;
  QFile file(m_fileName);
  
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug("parse: can't open `%s' for reading", qPrintable(m_fileName));
    return NULL;
  }

  bool block = false;

  while (!file.atEnd()) {
    QString line = file.readLine();
    line.chop(1); // remove newline character

    if (line.startsWith("#") && line.length() == 0) { // comment
      continue;
    }

    QStringList param = line.split(" ", Qt::SkipEmptyParts);

    if (block) {
      if (line.startsWith("ECHAR")) {
        block = false;
        charEnd();
      } else {
        charLineData(param);
      }
      continue;
    }
    
    if (line.startsWith("XSIZE")) { // xsize
      ds->putXSize(param[1].toDouble());
    } else if (line.startsWith("YSIZE")) { // ysize
      ds->putYSize(param[1].toDouble());
    } else if (line.startsWith("OFFSET")) { // offset
      ds->putOffset(param[1].toDouble());
    } else if (line.startsWith("CHAR")) { // char
      CharRecord* rec = new CharRecord(ds, param);
      ds->putCharRecord(rec);
      block = true;
    }
  }
  return ds;
}


void FontParser::charLineData(const QStringList& param)
{
  CharLineRecord* rec = new CharLineRecord(param);
  m_currentChar->lines.append(rec);
}

void FontParser::charEnd(void)
{
  m_currentChar = NULL;
}
