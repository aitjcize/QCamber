#include "roundsymbol.h"

#include <QtGui>

RoundSymbol::RoundSymbol(Params params): Symbol("r", params)
{
  m_d = params["d"].toDouble();
}

QRectF RoundSymbol::boundingRect() const
{
  return QRectF(-m_d / 2, -m_d / 2, m_d, m_d);
}

void RoundSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  painter->drawEllipse(-m_d / 2, -m_d / 2, m_d, m_d);
}
