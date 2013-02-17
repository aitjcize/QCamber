#include "linesymbol.h"

#include <QtGui>
#include <QRegExp>

#include "featuresparser.h"
#include "symbolfactory.h"

LineSymbol::LineSymbol(LineRecord* rec): Symbol("line", "line", rec->polarity)
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

  painterPath();
}

QPainterPath LineSymbol::painterPath()
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  // Set winding fill
  m_cachedPath.setFillRule(Qt::WindingFill);

  Symbol *symbol = SymbolFactory::create(m_sym_name, m_polarity);
  QPainterPath symbolPath = symbol->painterPath();
  if (symbolPath.boundingRect().height() != symbolPath.boundingRect().width()) {
    qDebug() << m_sym_name << "is not a symmetrics symbol, but we'll still "
      "try to draw lines with it";
  }
  delete symbol;

  qreal radius = (qreal)symbolPath.boundingRect().height() / 2;

  qreal sx = m_xs, sy = m_ys;
  qreal ex = m_xe, ey = m_ye;
  qreal dx = ex - sx, dy = ey - sy;
  qreal a = qAtan2(dy, dx);
  qreal rsina = radius * qSin(a), rcosa = radius * qCos(a);

  m_cachedPath.moveTo(sx + rsina, -(sy - rcosa));
  m_cachedPath.lineTo(sx - rsina, -(sy + rcosa));
  m_cachedPath.lineTo(ex - rsina, -(ey + rcosa));
  m_cachedPath.lineTo(ex + rsina, -(ey - rcosa));
  m_cachedPath.closeSubpath();
  m_cachedPath.addPath(symbolPath.translated(sx, -sy));
  m_cachedPath.addPath(symbolPath.translated(ex, -ey));

  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
