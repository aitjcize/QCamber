/**
 * @file   featuresdatastore.cpp
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

#include "featuresdatastore.h"

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

void FeaturesDataStore::putAttrlistItem(const QString& key,
    const QString& value)
{
  m_attrlist[key] = value;
}

void FeaturesDataStore::putSymbolName(int id, const QString& name)
{
  m_symbolNameMap[id] = name;
}

void FeaturesDataStore::putAttribName(int id, const QString& name)
{
  m_attribNameMap[id] = name;
}

void FeaturesDataStore::putAttribText(int id, const QString& text)
{
  m_attribTextMap[id] = text;
}

void FeaturesDataStore::putLine(LineRecord* rec)
{
  m_records.append(rec);

  if (rec->polarity == P) {
    ++m_posLineCountMap[m_symbolNameMap[rec->sym_num]];
  } else {
    ++m_negLineCountMap[m_symbolNameMap[rec->sym_num]];
  }
}

void FeaturesDataStore::putPad(PadRecord* rec)
{
  m_records.append(rec);

  if (rec->polarity == P) {
    ++m_posPadCountMap[m_symbolNameMap[rec->sym_num]];
  } else {
    ++m_negPadCountMap[m_symbolNameMap[rec->sym_num]];
  }
}

void FeaturesDataStore::putArc(ArcRecord* rec)
{
  m_records.append(rec);

  if (rec->polarity == P) {
    ++m_posArcCountMap[m_symbolNameMap[rec->sym_num]];
  } else {
    ++m_negArcCountMap[m_symbolNameMap[rec->sym_num]];
  }
}

void FeaturesDataStore::putText(TextRecord* rec)
{
  m_records.append(rec);

  if (rec->polarity == P) {
    ++m_posTextCount;
  } else {
    ++m_negTextCount;
  }
}

void FeaturesDataStore::putBarcode(BarcodeRecord* rec)
{
  m_records.append(rec);

  if (rec->polarity == P) {
    ++m_posBarcodeCount;
  } else {
    ++m_negBarcodeCount;
  }
}

void FeaturesDataStore::putSurfaceRecord(SurfaceRecord* rec)
{
  m_records.append(rec);

  if (rec->polarity == P) {
    ++m_posSurfaceCount;
  } else {
    ++m_negSurfaceCount;
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
