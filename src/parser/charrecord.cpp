/**
 * @file   charrecord.cpp
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

#include <QtCore/qmath.h>

#include "fontdatastore.h"

CharLineRecord::CharLineRecord(const QStringList& param)
{
  int i = 0;
  xs = param[++i].toDouble();
  ys = param[++i].toDouble();
  xe = param[++i].toDouble();
  ye = param[++i].toDouble();
  polarity = (param[++i] == "P")? P: N;
  shape = (param[++i] == "R")? R: S;
  width = param[++i].toDouble();
}

QPainterPath CharLineRecord::painterPath(qreal width_factor)
{
  QPainterPath path;

  qreal radius = width * width_factor / 2.0;
  qreal sx = xs, sy = ys;
  qreal ex = xe, ey = ye;
  qreal dx = ex - sx, dy = ey - sy;

  qreal a = qAtan2(dy, dx);
  qreal rsina = radius * qSin(a), rcosa = radius * qCos(a);

  path.moveTo(sx + rsina, -(sy - rcosa));
  path.lineTo(sx - rsina, -(sy + rcosa));
  path.lineTo(ex - rsina, -(ey + rcosa));
  path.lineTo(ex + rsina, -(ey - rcosa));
  path.closeSubpath();
  if (shape == R) {
    path.addEllipse(QPointF(sx, -sy), radius, radius);
    path.addEllipse(QPointF(ex, -ey), radius, radius);
  } else {
    qreal radius2 = radius * 2;
    path.addRect(sx-radius, -sy-radius, radius2, radius2);
    path.addRect(ex-radius, -ey-radius, radius2, radius2);
  }

  return path;
}

CharRecord::CharRecord(FontDataStore* ds, const QStringList& param): ds(ds)
{
  tchar = param[1].toLatin1()[0];
}

CharRecord::~CharRecord()
{
  for (QList<CharLineRecord*>::iterator it = lines.begin();
      it != lines.end(); ++it) {
    delete *it;
  }
}

QPainterPath CharRecord::painterPath(qreal width_factor)
{
  QPainterPath path;

  path.setFillRule(Qt::WindingFill);

  for (QList<CharLineRecord*>::iterator it = lines.begin();
      it != lines.end(); ++it) {
    CharLineRecord* rec = (*it);
    path.addPath(rec->painterPath(width_factor));
  }

  return path;
}
