#include "arcsymbol.h"

#include <QtGui>
#include <QRegExp>

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

ArcSymbol::ArcSymbol(ArcRecord* rec):
    Symbol("arc", "")
{
  m_xs = rec->xs;
  m_ys = rec->ys;
  m_xe = rec->xe;
  m_ye = rec->ye;
  m_xc = rec->xc;
  m_yc = rec->yc;
  m_sym_num = rec->sym_num;
  m_polarity = rec->polarity;
  m_dcode = rec->dcode;
  m_cw = rec->cw;
}

QRectF ArcSymbol::boundingRect() const
{
  return m_bounding;
}

void ArcSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  QPainterPath path;
  addShape(path);

  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  painter->drawPath(path);

  m_bounding = path.boundingRect();
}

void ArcSymbol::addShape(QPainterPath& path)
{
  qreal sx = m_xs, sy = m_ys;
  qreal ex = m_xe, ey = m_ye;
  qreal cx = m_xc, cy = m_yc;

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
