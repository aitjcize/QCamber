#include "squaresymbol.h"

#include <QtGui>

SquareSymbol::SquareSymbol(Params params): Symbol("s", params)
{
  m_s = params["s"].toDouble();
}

QRectF SquareSymbol::boundingRect() const
{
  return QRectF(-m_s / 2, -m_s / 2, m_s, m_s);
}

void SquareSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  painter->drawRect(-m_s / 2, -m_s / 2, m_s, m_s);
}
