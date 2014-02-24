/**
 * @file   surfacesymbol.cpp
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

#include "surfacesymbol.h"

#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

#include <QtGui>
#include <QRegExp>

#include "context.h"

SurfaceSymbol::SurfaceSymbol(const SurfaceRecord* rec):
  Symbol("Surface", "Surface", rec->polarity, rec->attrib),
  m_islandCount(0), m_holeCount(0)
{
  m_dcode = rec->dcode;
  m_polygons = rec->polygons;

  m_bounding = painterPath().boundingRect();
}

QString SurfaceSymbol::infoText(void)
{
  QPointF c = m_bounding.center();
  QString info = QString("Surface, XC=%1, YC=%2, Islands=%3, Holes=%4, %5") \
    .arg(c.x()).arg(c.y()) \
    .arg(m_islandCount).arg(m_holeCount) \
    .arg((m_polarity == P)? "POS": "NEG");
  return info;
}

QString SurfaceSymbol::longInfoText(void)
{
  QPointF c = m_bounding.center();
  QString result(
      "Surface\n\n"
      "XC\t= %1\n"
      "YC\t= %2\n"
      "Islands\t= %3\n"
      "Holes\t= %4\n"
      "Polarity\t= %5\n"
  );
  return result \
    .arg(c.x()).arg(c.y()) \
    .arg(m_islandCount).arg(m_holeCount) \
    .arg((m_polarity == P)? "POS": "NEG");
}

QPainterPath SurfaceSymbol::painterPath(void)
{
  QPainterPath path;

  m_islandCount = 0;
  m_holeCount = 0;

  for (QList<PolygonRecord*>::iterator it = m_polygons.begin();
      it != m_polygons.end(); ++it) {
    PolygonRecord* rec = (*it);
    path.addPath(rec->painterPath());
    if (rec->poly_type == PolygonRecord::I) {
      ++m_islandCount;
    } else {
      ++m_holeCount;
    }
  }

  return path;
}
