#include "measuregraphicsitem.h"

#include <QtGui>

MeasureGraphicsItem::MeasureGraphicsItem(QRectF rect): m_rect(rect)
{
  
}

QRectF MeasureGraphicsItem::boundingRect() const
{
  return m_rect;
}

void MeasureGraphicsItem::setRect(const QRectF& rect)
{
  prepareGeometryChange();
  m_rect = rect;
  update();
}

void MeasureGraphicsItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setPen(QPen(Qt::white));
  painter->setBrush(Qt::transparent);
  painter->drawRect(m_rect);
  painter->drawLine(QLineF(m_rect.topLeft(), m_rect.bottomRight()));
}
