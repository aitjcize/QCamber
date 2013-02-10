#include "symbol.h"
#include <QDebug>

Symbol::Symbol(QString name, QString pattern, Polarity polarity):
  m_name(name), m_pattern(pattern), m_polarity(polarity), m_valid(false)
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
  if (m_polarity == P) {
    painter->setPen(QPen(Qt::red, 0));
    painter->setBrush(Qt::red);
  } else {
    painter->setPen(QPen(Qt::white, 0));
    painter->setBrush(Qt::white);
  }

  painterPath();
  painter->drawPath(m_cachedPath);
}

QPainterPath Symbol::painterPath(void)
{
  m_cachedPath = QPainterPath();
  m_bounding = m_cachedPath.boundingRect();
  return m_cachedPath;
}

void Symbol::invalidate(void)
{
  m_valid = false;
}
