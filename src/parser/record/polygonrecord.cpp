#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

PolygonRecord::PolygonRecord(const QStringList& param)
{
  int i = 0;
  xbs = param[++i].toDouble();
  ybs = param[++i].toDouble();
  poly_type = (param[++i] == "I")? PolygonRecord::I : PolygonRecord::H;
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
  return path;
}
