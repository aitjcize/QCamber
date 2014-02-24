/**
 * @file   barcoderecord.cpp
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

#include <QPainterPath>

#include "featuresparser.h"
#include "symbolfactory.h"

BarcodeRecord::BarcodeRecord(FeaturesDataStore* ds, const QStringList& param,
    const AttribData& attr):
  TextRecord(ds, QStringList(), attr)
{
  int i = 0;
  x = param[++i].toDouble();
  y = param[++i].toDouble();
  barcode = param[++i];
  font = param[++i];
  polarity = (param[++i] == "P")? P: N;
  orient = (Orient)param[++i].toInt();
  e = param[++i];
  w = param[++i].toDouble();
  h = param[++i].toDouble();
  fasc = (param[++i] == "Y");
  cs = (param[++i] == "Y");
  bg = (param[++i] == "Y");
  astr = (param[++i] == "Y");
  astr_pos = (param[++i] == "T")? BarcodeRecord::T : BarcodeRecord::B;
  text = dynamicText(param[++i]);
}

Symbol* BarcodeRecord::createSymbol(void) const
{
  Symbol* symbol = new BarcodeSymbol(this);
  setTransform(symbol);
  return symbol;
}
