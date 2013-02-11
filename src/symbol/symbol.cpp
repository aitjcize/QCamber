#include "symbol.h"
#include <QDebug>

Symbol::Symbol(QString name, QString pattern, Polarity polarity):
  m_name(name), m_pattern(pattern), m_color(Qt::red), m_polarity(polarity),
  m_valid(false)
{
}

Symbol::~Symbol()
{
  for (QList<Symbol*>::iterator it = m_symbols.begin();
      it != m_symbols.end(); ++it) {
    delete (*it);
  }
}

QString Symbol::name(void)
{
  return m_name;
}

QRectF Symbol::boundingRect() const
{
  return m_bounding;
}

void Symbol::setColor(QColor color)
{
  m_color = color;

  for (QList<Symbol*>::iterator it = m_symbols.begin();
      it != m_symbols.end(); ++it) {
    (*it)->setColor(color);
  }
}

void Symbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget)
{
  if (m_polarity == P) {
    painter->setPen(QPen(m_color, 0));
    painter->setBrush(m_color);
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

void Symbol::addToSymbols(Symbol* symbol)
{
  m_symbols.append(symbol);
}
