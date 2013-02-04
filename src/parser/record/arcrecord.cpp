#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

void ArcRecord::addShape(QPainterPath& path, qreal ox, qreal oy)
{
  qreal sx = xs, sy = ys;
  qreal ex = xe, ey = ye;
  qreal cx = xc, cy = yc;

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

  if (cw) {
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
}

void ArcRecord::add(QGraphicsScene* scene)
{
  QPainterPath path;
  addShape(path, 0, 0);
  scene->addPath(path);
}

