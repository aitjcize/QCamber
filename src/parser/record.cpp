#include "record.h"

#include <QDebug>
#include <cmath>

void PolygonRecord::addShape(QPainterPath& path)
{
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

      qreal rs = sqrt(sax * sax + say * say);
      qreal re = sqrt(eax * eax + eay * eay);

      qreal sa = atan(say / sax);
      qreal ea = atan(eay / eax);

      if (ea <= 0 && (eax < 0)) {
        ea += M_PI;
      } else if (ea > 0 && (eax < 0 || eay < 0)) {
        ea += M_PI;
      }

      if (sa <= 0 && (sax < 0)) {
        sa += M_PI;
      } else if (sa > 0 && (sax < 0 || say < 0)) {
        sa += M_PI;
      }

      if (op->cw) {
        if (sa < ea) {
          sa += 2 * M_PI;
        }
        for (qreal a = sa; a >= ea; a -= 0.01) {
          qreal rad = (rs * (ea - a) + re * (a - sa)) / (ea - sa);
          path.lineTo(cx + rad * cos(a), -(cy + rad * sin(a)));
        }
      } else {
        if (ea < sa) {
          ea += 2 * M_PI;
        }
        for (qreal a = sa; a <= ea; a += 0.01) {
          qreal rad = (rs * (ea - a) + re * (a - sa)) / (ea - sa);
          path.lineTo(cx + rad * cos(a), -(cy + rad * sin(a)));
        }
      }
      path.lineTo(ex, -ey);
      lx = ex; ly = ey;
    }
  }
  path.closeSubpath();
}

void SurfaceRecord::addShape(QPainterPath& path)
{
  for (QList<PolygonRecord*>::iterator it = polygons.begin();
      it != polygons.end(); ++it) {
    PolygonRecord* rec = (*it);
    rec->addShape(path);
  }
}
