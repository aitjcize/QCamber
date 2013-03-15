#include "arcsymbol.h"

#include <QtGui>

#include "featuresparser.h"
#include "macros.h"

static void addArc(QPainterPath& path, qreal sx, qreal sy,
    qreal ex, qreal ey, qreal cx, qreal cy, bool cw)
{
  qreal sax = sx - cx, say = sy - cy;
  qreal eax = ex - cx, eay = ey - cy;

  qreal r = qSqrt(sax * sax + say * say);

  qreal sa = qAtan2(say, sax);
  qreal ea = qAtan2(eay, eax);

  if (cw) {
    if (sa < ea) {
      sa += 2 * M_PI;
    }
  } else {
    if (ea < sa) {
      ea += 2 * M_PI;
    }
  }

  path.arcTo(QRectF(cx -r, -cy -r, r *2, r *2), sa * R2D, (ea - sa) * R2D);
  path.lineTo(ex, -ey);
}

ArcSymbol::ArcSymbol(ArcRecord* rec):
    Symbol("Arc", "Arc", rec->polarity)
{
  m_xs = rec->xs;
  m_ys = rec->ys;
  m_xe = rec->xe;
  m_ye = rec->ye;
  m_xc = rec->xc;
  m_yc = rec->yc;
  m_sym_num = rec->sym_num;
  m_dcode = rec->dcode;
  m_cw = rec->cw;
  m_sym_name = static_cast<FeaturesDataStore*>(rec->ds)->\
               symbolNameMap()[rec->sym_num];

  m_bounding = painterPath().boundingRect();
}

QString ArcSymbol::infoText(void)
{
  QString info = QString("Arc, XC=%1, YC=%2, XS=%3, YS=%4, XE=%5, YE=%6, "
      "%7, %8, %9") \
    .arg(m_xc).arg(m_yc) \
    .arg(m_xs).arg(m_ys) \
    .arg(m_xe).arg(m_ye) \
    .arg(m_sym_name) \
    .arg((m_polarity == P)? "POS": "NEG") \
    .arg(m_cw? "CW": "CCW");
  return info;
}

QPainterPath ArcSymbol::painterPath(void)
{
  QPainterPath path;

  qreal sx = m_xs, sy = m_ys;
  qreal ex = m_xe, ey = m_ye;
  qreal cx = m_xc, cy = m_yc;

  qreal rad = m_sym_name.right(m_sym_name.length() -1).toDouble() / 1000.0;
  qreal hr = rad / 2;
  qreal dx = sx - cx, dy = sy - cy;
  qreal ds = qSqrt(dx * dx + dy * dy);

  // normalize
  dx /= ds; dy /= ds;

  qreal sex, sey; // start point expended
  qreal ssx, ssy; // start point shrinked

  sex = sx + dx * hr;
  sey = sy + dy * hr;

  ssx = sx - dx * hr;
  ssy = sy - dy * hr;

  dx = ex - cx, dy = ey - cy;
  ds = qSqrt(dx * dx + dy * dy);

  // normalize
  dx /= ds; dy /= ds;

  qreal eex, eey; // end point expended
  qreal esx, esy; // end point shrinked

  eex = ex + dx * hr;
  eey = ey + dy * hr;

  esx = ex - dx * hr;
  esy = ey - dy * hr;

  path.moveTo(eex, -eey);
  addArc(path, eex, eey, sex, sey, cx, cy, !m_cw);
  addArc(path, sex, sey, ssx, ssy, sx, sy, !m_cw);
  addArc(path, ssx, ssy, esx, esy, cx, cy, m_cw);
  addArc(path, esx, esy, eex, eey, ex, ey, !m_cw);

  path.closeSubpath();

  return path;
}
