#include "originsymbol.h"

#include <QtGui>
#include <QRegExp>


OriginSymbol::OriginSymbol():
    Symbol("Origin", "Origin", P)
{
  m_rad = 0.1;
}

QRectF OriginSymbol::boundingRect() const
{
  return QRectF(-m_rad, -m_rad, m_rad * 2, m_rad * 2);
}

void OriginSymbol::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  qreal srad = m_rad * 0.7;
  painter->setPen(QPen(m_pen.color(), 0.005));
  painter->setBrush(Qt::transparent);

  painter->drawEllipse(QPointF(0, 0), srad, srad);
  painter->drawLine(QPointF(-m_rad, 0), QPointF(m_rad, 0));
  painter->drawLine(QPointF(0, m_rad), QPointF(0, -m_rad));
  painter->drawLine(QPointF(-srad, -srad), QPointF(srad, srad));
  painter->drawLine(QPointF(srad, -srad), QPointF(-srad, srad));
}
