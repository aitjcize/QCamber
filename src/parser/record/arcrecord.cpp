#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

static void addArc(QPainterPath& path, qreal sx, qreal sy,
    qreal ex, qreal ey, qreal cx, qreal cy, bool cw)
{
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

void ArcRecord::addShape(QPainterPath& path, qreal ox, qreal oy)
{
  qreal sx = ox + xs, sy = oy + ys;
  qreal ex = ox + xe, ey = oy + ye;
  qreal cx = ox + xc, cy = oy + yc;

  qreal rad = 0.2;
  qreal hr = rad / 2;
  qreal dx = sx - cx, dy = sy - cy;
  qreal ds = sqrt(dx * dx + dy * dy);

  // normalize
  dx /= ds; dy /= ds;

  qreal sex, sey; // start point expended
  qreal ssx, ssy; // start point shrinked

  sex = sx + dx * hr;
  sey = sy + dy * hr;

  ssx = sx - dx * hr;
  ssy = sy - dy * hr;

  dx = ex - cx, dy = ey - cy;
  ds = sqrt(dx * dx + dy * dy);

  // normalize
  dx /= ds; dy /= ds;

  qreal eex, eey; // end point expended
  qreal esx, esy; // end point shrinked

  eex = ex + dx * hr;
  eey = ey + dy * hr;

  esx = ex - dx * hr;
  esy = ey - dy * hr;

  path.moveTo(eex, -eey);
  addArc(path, eex, eey, sex, sey, cx, cy, true);
  addArc(path, sex, sey, ssx, ssy, sx, sy, true);
  addArc(path, ssx, ssy, esx, esy, cx, cy, false);
  addArc(path, esx, esy, eex, eey, ex, ey, true);

  path.closeSubpath();
}

void ArcRecord::add(QGraphicsScene* scene)
{
  QPainterPath path;
  addShape(path, 0, 0);
  scene->addPath(path);
}
