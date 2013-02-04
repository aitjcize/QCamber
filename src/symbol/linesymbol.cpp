#include "linesymbol.h"

#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

#include <QtGui>
#include <QRegExp>

#include "context.h"

extern Context ctx;

LineSymbol::LineSymbol(LineRecord* rec): Symbol("user", "user"), m_rec(rec)
{
}

QRectF LineSymbol::boundingRect() const
{
  return bounding;
}

void LineSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  QPainterPath path;
  path.setFillRule(Qt::WindingFill);
  addShape(path);
  path.setFillRule(Qt::WindingFill);

  painter->setPen(QPen(Qt::blue, 0));
  painter->setBrush(Qt::blue);
  painter->drawPath(path);

  bounding = path.boundingRect();
}

void LineSymbol::addShape(QPainterPath& path)
{
  m_rec->addShape(path, pos().x(), -pos().y());
}
