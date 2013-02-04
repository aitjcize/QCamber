#include "linesymbol.h"

#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

#include <QtGui>
#include <QRegExp>

#include "context.h"

extern Context ctx;

LineSymbol::LineSymbol(LineRecord* rec): Symbol("user", "user")
{
  m_xs = rec->xs;
  m_ys = rec->ys;
  m_xe = rec->xe;
  m_ye = rec->ye;
  m_sym_num = rec->sym_num;
  m_sym_name = rec->ds->symbolNameMap()[rec->sym_num];
  m_polarity = rec->polarity;
  m_dcode = rec->dcode;
}

QRectF LineSymbol::boundingRect() const
{
  return bounding;
}

void LineSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  QPainterPath path;
  addPath(path, false);
  path.setFillRule(Qt::WindingFill);

  painter->setPen(QPen(Qt::blue, 0));
  painter->setBrush(Qt::blue);
  painter->drawPath(path);

  bounding = path.boundingRect();
}

void LineSymbol::addShape(QPainterPath& path)
{
  addPath(path, true);
}

void LineSymbol::addPath(QPainterPath& path, bool offset)
{
  QString sym_name = m_sym_name;
  qreal radius = (qreal)sym_name.right(sym_name.length()-1).toDouble()/2/1000;

  qreal sx = m_xs, sy = m_ys;
  qreal ex = m_xe, ey = m_ye;
  qreal dx = ex - sx, dy = ey - sy;
  qreal a = qAtan2(dy, dx);
  qreal rsina = radius * qSin(a), rcosa = radius * qCos(a);

  if (offset) {
    sx += pos().x();
    sy += pos().y();
    ex += pos().x();
    ey += pos().y();
  }

  // Extend to make square cap
  if (sym_name[0] == 's') {
    sx -= rcosa;
    sy -= rsina;
    ex += rcosa;
    ey += rsina;
  }

  path.moveTo(sx + rsina, -(sy - rcosa));
  path.lineTo(sx - rsina, -(sy + rcosa));
  path.lineTo(ex - rsina, -(ey + rcosa));
  path.lineTo(ex + rsina, -(ey - rcosa));
  path.closeSubpath();

  if (sym_name[0] == 'r') {
    path.addEllipse(QPointF(sx, -sy), radius, radius);
    path.addEllipse(QPointF(ex, -ey), radius, radius);
  }
}
