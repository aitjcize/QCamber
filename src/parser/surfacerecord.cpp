/**
 * @file   surfacerecord.cpp
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

#include <QtCore>
#include <QPainterPath>

#include "featuresparser.h"
#include "macros.h"
#include "surfacesymbol.h"

PolygonRecord::PolygonRecord(const QStringList& param)
{
  int i = 0;
  xbs = param[++i].toDouble();
  ybs = param[++i].toDouble();
  poly_type = (param[++i] == "I")? PolygonRecord::I : PolygonRecord::H;
}

PolygonRecord::~PolygonRecord()
{
  for (QList<SurfaceOperation*>::iterator it = operations.begin();
      it != operations.end(); ++it) {
    delete *it;
  }
}

QPainterPath PolygonRecord::painterPath(void)
{
  QPainterPath path;
  qreal lx, ly;

  lx = xbs; ly = ybs;
  path.moveTo(lx, -ly);

  for (QList<SurfaceOperation*>::iterator it = operations.begin();
      it != operations.end(); ++it) {
    SurfaceOperation* op = *it;
    if (op->type == SurfaceOperation::SEGMENT) {
      lx = op->x; ly = op->y;
      path.lineTo(lx, -ly);
    } else if (op->type == SurfaceOperation::CURVE) {
      qreal sx = lx, sy = ly;
      qreal ex = op->xe, ey = op->ye;
      qreal cx = op->xc, cy = op->yc;

      qreal sax = sx - cx, say = sy - cy;
      qreal eax = ex - cx, eay = ey - cy;

      qreal r = qSqrt(sax * sax + say * say);

      qreal sa = qAtan2(say, sax);
      qreal ea = qAtan2(eay, eax);

      if (op->cw) {
        if (sa <= ea) {
          sa += 2 * M_PI;
        }
      } else {
        if (ea <= sa) {
          ea += 2 * M_PI;
        }
      }

      path.arcTo(QRectF(cx -r, -cy -r, r *2, r *2), sa * R2D, (ea - sa) * R2D);
      path.lineTo(ex, -ey);
      lx = ex; ly = ey;
    }
  }
  path.closeSubpath();
  return path;
}

SurfaceRecord::SurfaceRecord(FeaturesDataStore* ds, const QStringList& param,
    const AttribData& attr):
  Record(ds, attr)
{
  int i = 0;
  polarity = (param[++i] == "P")? P: N;
  dcode = param[++i].toInt();
}

SurfaceRecord::~SurfaceRecord()
{
  for (QList<PolygonRecord*>::iterator it = polygons.begin();
      it != polygons.end(); ++it) {
    delete *it;
  }
}

Symbol* SurfaceRecord::createSymbol(void) const
{
  return new SurfaceSymbol(this);
}
