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

      qreal rs = qSqrt(sax * sax + say * say);
      qreal re = qSqrt(eax * eax + eay * eay);

      qreal sa = qAtan2(say, sax);
      qreal ea = qAtan2(eay, eax);

      if (op->cw) {
        if (sa < ea) {
          sa += 2 * M_PI;
        }
        for (qreal a = sa; a >= ea; a -= 0.01) {
          qreal rad = (rs * (ea - a) + re * (a - sa)) / (ea - sa);
          path.lineTo(cx + rad * qCos(a), -(cy + rad * qSin(a)));
        }
      } else {
        if (ea < sa) {
          ea += 2 * M_PI;
        }
        for (qreal a = sa; a <= ea; a += 0.01) {
          qreal rad = (rs * (ea - a) + re * (a - sa)) / (ea - sa);
          path.lineTo(cx + rad * qCos(a), -(cy + rad * qSin(a)));
        }
      }
      path.lineTo(ex, -ey);
      lx = ex; ly = ey;
    }
  }
  path.closeSubpath();
}

void PolygonRecord::add(QGraphicsScene *scene)
{
}
