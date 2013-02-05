#include "linesymbol.h"
#include "symbolfactory.h"
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
  //make sure start is at left hand side of end
  if(m_xs > m_xe){
    qreal tmp = m_xs;
    m_xs = m_xe;
    m_xe = tmp;
    tmp = m_ys;
    m_ys = m_ye;
    m_ye = tmp;
  }
}

QRectF LineSymbol::boundingRect() const
{
  return bounding;
}

void LineSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  QPainterPath path = painterPath();
  path.setFillRule(Qt::WindingFill);

  painter->setPen(QPen(Qt::blue, 0));
  painter->setBrush(Qt::blue);
  painter->drawPath(path);

  bounding = path.boundingRect();
}

QPainterPath LineSymbol::painterPath()
{
  Symbol *symbol = SymbolFactory::create(m_sym_name);
  QPainterPath symbolPath = symbol->painterPath();
  if(symbolPath.boundingRect().height() != symbolPath.boundingRect().width()){
    qDebug()<<m_sym_name<<"is not a symmetrics symbol, but we'll still try to draw lines with it";
  }
  delete symbol;
  QPainterPath path;
  QString sym_name = m_sym_name;
  qreal radius = (qreal)symbolPath.boundingRect().height()/2;

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
