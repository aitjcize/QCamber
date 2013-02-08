#include "symbol.h"
#include <QDebug>

Symbol::Symbol(QString name, QString pattern):
  m_name(name), m_pattern(pattern), m_valid(false)
{
  
}

QString Symbol::name(void)
{
  return m_name;
}

QRectF Symbol::boundingRect() const
{
  return m_bounding;
}

void Symbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);

  painterPath();
  painter->drawPath(m_cachedPath);
}
