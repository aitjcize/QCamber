#include "originsymbol.h"

#include <QtGui>
#include <QRegExp>


OriginSymbol::OriginSymbol():
    Symbol("Origin", "Origin", P)
{
}

QRectF OriginSymbol::boundingRect() const
{
}

void OriginSymbol::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  qreal rad = 0.1, mrad = rad * 0.7;
  painter->setPen(QPen(Qt::white, 0.005));
  painter->setBrush(Qt::transparent);

  painter->drawEllipse(QPointF(0, 0), mrad, mrad);
  painter->drawLine(QPointF(-rad, 0), QPointF(rad, 0));
  painter->drawLine(QPointF(0, rad), QPointF(0, -rad));
  painter->drawLine(QPointF(-mrad, -mrad), QPointF(mrad, mrad));
  painter->drawLine(QPointF(mrad, -mrad), QPointF(-mrad, mrad));
}
