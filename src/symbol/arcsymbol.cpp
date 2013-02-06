#include "arcsymbol.h"

#include <QtGui>
#include <QRegExp>

static void addArc(QPainterPath& m_cachedPath, qreal sx, qreal sy,
    qreal ex, qreal ey, qreal cx, qreal cy, bool cw)
{
  qreal sax = sx - cx, say = sy - cy;
  qreal eax = ex - cx, eay = ey - cy;

  qreal rs = qSqrt(sax * sax + say * say);
  qreal re = qSqrt(eax * eax + eay * eay);

  qreal sa = qAtan2(say, sax);
  qreal ea = qAtan2(eay, eax);

  if (cw) {
    if (sa < ea) {
      sa += 2 * M_PI;
    }
    for (qreal a = sa; a >= ea; a -= 0.01) {
      qreal rad = (rs * (ea - a) + re * (a - sa)) / (ea - sa);
      m_cachedPath.lineTo(cx + rad * qCos(a), -(cy + rad * qSin(a)));
    }
  } else {
    if (ea < sa) {
      ea += 2 * M_PI;
    }
    for (qreal a = sa; a <= ea; a += 0.01) {
      qreal rad = (rs * (ea - a) + re * (a - sa)) / (ea - sa);
      m_cachedPath.lineTo(cx + rad * qCos(a), -(cy + rad * qSin(a)));
    }
  }
  m_cachedPath.lineTo(ex, -ey);
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

  painterPath();
}

QPainterPath ArcSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();
  m_valid = true;

  qreal sx = m_xs, sy = m_ys;
  qreal ex = m_xe, ey = m_ye;
  qreal cx = m_xc, cy = m_yc;

  qreal rad = 0.2;
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

  m_cachedPath.moveTo(eex, -eey);
  addArc(m_cachedPath, eex, eey, sex, sey, cx, cy, true);
  addArc(m_cachedPath, sex, sey, ssx, ssy, sx, sy, true);
  addArc(m_cachedPath, ssx, ssy, esx, esy, cx, cy, false);
  addArc(m_cachedPath, esx, esy, eex, eey, ex, ey, true);

  m_cachedPath.closeSubpath();

  m_bounding = m_cachedPath.boundingRect();
  return m_cachedPath;
}
