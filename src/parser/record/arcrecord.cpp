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

  if (sa <= 0 && (sax < 0)) {
    sa += M_PI;
  } else if (sa > 0 && (sax < 0 || say < 0)) {
    sa += M_PI;
  }

  if (ea <= 0 && (eax < 0)) {
    ea += M_PI;
  } else if (ea > 0 && (eax < 0 || eay < 0)) {
    ea += M_PI;
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

  qreal sax = sx - cx, say = sy - cy;
  qreal eax = ex - cx, eay = ey - cy;

  qreal rs = sqrt(sax * sax + say * say);
  qreal re = sqrt(eax * eax + eay * eay);

  qreal hr = rad / 2;
  qreal dx, dy, ds;
  qreal rx, ry;

  qreal sa = atan(say / sax);
  if (sa <= 0 && (sax < 0)) {
    sa += M_PI;
  } else if (sa > 0 && (sax < 0 || say < 0)) {
    sa += M_PI;
  }

  qreal ea = atan(eay / eax);
  if (ea <= 0 && (eax < 0)) {
    ea += M_PI;
  } else if (ea > 0 && (eax < 0 || eay < 0)) {
    ea += M_PI;
  }

#define RAD(a) ((rs * (ea - a) + re * (a - sa)) / (ea - sa))
  qreal sp1x =  (cx + RAD(sa) * cos(sa));
  qreal sp1y = -(cy + RAD(sa) * sin(sa));
  qreal sp2x =  (cx + RAD(sa-0.01) * cos(sa-0.01));
  qreal sp2y = -(cy + RAD(sa-0.01) * sin(sa-0.01));

  dx = sp2x - sp1x; dy = sp2y - sp1y;
  ds = sqrt(dx * dx + dy * dy);
  rx = dy / ds; ry = -dx / ds;

  qreal sex, sey; // start point expended
  qreal ssx, ssy; // start point shrinked

  sex = sx + rx * hr;
  sey = sy + ry * hr;

  ssx = sx - rx * hr;
  ssy = sy - ry * hr;

  qreal ep1x =  (cx + RAD(ea) * cos(ea));
  qreal ep1y = -(cy + RAD(ea) * sin(ea));
  qreal ep2x =  (cx + RAD(ea+0.01) * cos(ea+0.01));
  qreal ep2y = -(cy + RAD(ea+0.01) * sin(ea+0.01));

  dx = ep2x - ep1x; dy = ep2y - ep1y;
  ds = sqrt(dx * dx + dy * dy);
  rx = dy / ds; ry = -dx / ds;

  qreal eex, eey; // end point expended
  qreal esx, esy; // end point shrinked

  eex = ex + rx * hr;
  eey = ey + ry * hr;

  esx = ex - rx * hr;
  esy = ey - ry * hr;

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
