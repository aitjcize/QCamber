#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

void PolygonRecord::addShape(QPainterPath& path, qreal ox, qreal oy)
{
  qreal lx, ly;
  lx = ox + xbs; ly = oy + ybs;
  path.moveTo(lx, -ly);

  for (QList<SurfaceOperation*>::iterator it = operations.begin();
      it != operations.end(); ++it) {
    SurfaceOperation* op = *it;
    if (op->type == SurfaceOperation::SEGMENT) {
      lx = ox + op->x; ly = oy + op->y;
      path.lineTo(lx, -ly);
    } else if (op->type == SurfaceOperation::CURVE) {
      qreal sx = lx, sy = ly;
      qreal ex = ox + op->xe, ey = oy + op->ye;
      qreal cx = ox + op->xc, cy = oy + op->yc;

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

void PolygonRecord::paint(QPainter *painter)
{
}
