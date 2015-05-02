/**
 * @file   padrecord.cpp
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

#include "record.h"

#include <cmath>

#include <QMatrix>
#include <QPainterPath>
#include <QTransform>

#include "featuresparser.h"
#include "symbolfactory.h"

PadRecord::PadRecord(FeaturesDataStore* ds, const QStringList& param,
    const AttribData& attr):
  Record(ds, attr)
{
  int i = 0;
  x = param[++i].toDouble();
  y = param[++i].toDouble();
  sym_num = param[++i].toInt();
  polarity = (param[++i] == "P")? P: N;
  dcode = param[++i].toInt();
  orient = (Orient)param[++i].toInt();
  sym_name = ds->symbolNameMap()[sym_num];
}

Symbol* PadRecord::createSymbol(void) const
{
  Symbol* symbol = SymbolFactory::create(sym_name, polarity, attrib);
  symbol->setPos(x, -y);

  if (orient >= M_0) {
    QTransform trans;
    trans.scale(-1, 1);
    symbol->setTransform(trans);
  }
  symbol->setRotation((orient % 4) * 90);
  return symbol;
}
