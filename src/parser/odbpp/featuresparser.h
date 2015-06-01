/**
 * @file   featuresparser.h
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

#ifndef __FEATURES_PARSER_H__
#define __FEATURES_PARSER_H__

#include "featuresdatastore.h"

#include "parser.h"

class FeaturesParser: public Parser {
public:
  FeaturesParser(const QString& filename);
  virtual ~FeaturesParser();

  virtual FeaturesDataStore* parse(void);

private:
  void putAttrlist(const StructuredTextDataStore* ds);
  void parseSymbolName(const QString& line);
  void parseAttribName(const QString& line);
  void parseAttribText(const QString& line);
  void parseLine(const QString& line);
  void parsePad(const QString& line);
  void parseArc(const QString& line);
  void parseText(const QString& line);
  void parseBarcode(const QString& line);
  void parseSurfaceStart(const QString& line);
  void parseSurfaceLineData(const QString& line);
  void parseSurfaceEnd(void);

  void parseAttributes(const QString& line, QStringList* param,
      AttribData* attrib);

  FeaturesDataStore* m_ds;
  SurfaceRecord* m_currentSurface;
};

#endif /* __FEATURES_PARSER_H__ */
