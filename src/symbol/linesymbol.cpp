#include "linesymbol.h"

#include <QtGui>
#include <QRegExp>

#include "featuresparser.h"
#include "symbolpool.h"

LineSymbol::LineSymbol(const LineRecord* rec):
  Symbol("Line", "Line", rec->polarity)
{
  m_xs = rec->xs;
  m_ys = rec->ys;
  m_xe = rec->xe;
  m_ye = rec->ye;
  m_sym_num = rec->sym_num;
  m_sym_name = static_cast<FeaturesDataStore*>(rec->ds)->\
               symbolNameMap()[rec->sym_num];
  m_dcode = rec->dcode;

  //make sure start is at left hand side of end
  if (m_xs > m_xe) {
    qreal tmp = m_xs;
    m_xs = m_xe;
    m_xe = tmp;
    tmp = m_ys;
    m_ys = m_ye;
    m_ye = tmp;
  }

  m_bounding = painterPath().boundingRect();
}

QString LineSymbol::infoText(void)
{
  QString info = QString("Line, XS=%1, YS=%2, XE=%3, YE=%4, %5, %6") \
    .arg(m_xs).arg(m_ys) \
    .arg(m_xe).arg(m_ye) \
    .arg(m_sym_name) \
    .arg((m_polarity == P)? "POS": "NEG");
  return info;
}

QPainterPath LineSymbol::painterPath()
{
  QPainterPath path;

  // Set winding fill
  path.setFillRule(Qt::WindingFill);

  Symbol *symbol = SYMBOLPOOL->get(m_sym_name, m_polarity);
  QPainterPath symbolPath = symbol->painterPath();
  if (symbolPath.boundingRect().height() != symbolPath.boundingRect().width()) {
    qDebug() << m_sym_name << "is not a symmetrics symbol, but we'll still "
      "try to draw lines with it";
  }

  qreal radius = (qreal)symbolPath.boundingRect().height() / 2;

  qreal sx = m_xs, sy = m_ys;
  qreal ex = m_xe, ey = m_ye;
  qreal dx = ex - sx, dy = ey - sy;
  qreal a = qAtan2(dy, dx);
  qreal rsina = radius * qSin(a), rcosa = radius * qCos(a);

  path.moveTo(sx + rsina, -(sy - rcosa));
  path.lineTo(sx - rsina, -(sy + rcosa));
  path.lineTo(ex - rsina, -(ey + rcosa));
  path.lineTo(ex + rsina, -(ey - rcosa));
  path.closeSubpath();
  path.addPath(symbolPath.translated(sx, -sy));
  path.addPath(symbolPath.translated(ex, -ey));

  return path;
}
