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
  addShape(path);
  path.setFillRule(Qt::WindingFill);

  painter->setPen(QPen(Qt::blue, 0));
  painter->setBrush(Qt::blue);
  painter->drawPath(path);

  bounding = path.boundingRect();
}

void LineSymbol::addShape(QPainterPath& path)
{

  QString sym_name = m_sym_name;
  qreal radius = (qreal)sym_name.right(sym_name.length()-1).toDouble()/2/1000;
  QPointF p1s(m_xs, -m_ys), p1e(m_xe, -m_ye), p2s, p2e, ps, pe;
  ps = p2s = p1s;
  pe = p2e = p1e;

  QPointF delta;
  qreal angle = qAtan2(m_ye - m_ys, m_xe - m_xs);
  delta.setX(-qSin(angle));
  delta.setY(-qCos(angle));

  delta*= radius;
  p1s += delta;
  p1e += delta;
  p2s -= delta;
  p2e -= delta;

  path.moveTo(p1s);
  path.lineTo(p1e);
  path.lineTo(p2e);
  path.lineTo(p2s);
  path.lineTo(p1s);
  if(sym_name[0]=='r'){
    //QPointF pbr, ptl;
    //if(m>0){
    //}
    path.addEllipse(ps, radius, radius);
    path.addEllipse(pe, radius, radius);
  }
}
