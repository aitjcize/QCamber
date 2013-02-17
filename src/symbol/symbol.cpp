#include "symbol.h"
#include <QDebug>

Symbol::Symbol(QString name, QString pattern, Polarity polarity):
  m_name(name), m_pattern(pattern), m_pen(QPen(Qt::red, 0)), m_brush(Qt::red),
  m_polarity(polarity), m_valid(false)
{
  setHandlesChildEvents(false);
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
  if (m_symbols.count()) {
    return QGraphicsItemGroup::boundingRect();
  } else {
    return m_bounding;
  }
}

void Symbol::setPen(QPen pen)
{
  m_pen = pen;

  for (QList<Symbol*>::iterator it = m_symbols.begin();
      it != m_symbols.end(); ++it) {
    (*it)->setPen(pen);
  }
}

void Symbol::setBrush(QBrush brush)
{
  m_brush = brush;

  for (QList<Symbol*>::iterator it = m_symbols.begin();
      it != m_symbols.end(); ++it) {
    (*it)->setBrush(brush);
  }
}

void Symbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget)
{
  // Paint item group
  QGraphicsItemGroup::paint(painter, option, widget);

  // Paint painterPath
  if (m_polarity == P) {
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
  } else {
    painter->setPen(QPen(BG_COLOR, 0));
    painter->setBrush(BG_COLOR);
  }

  painterPath();
  painter->drawPath(m_cachedPath);
}

void Symbol::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  setPen(QPen(Qt::blue, 0));
  setBrush(Qt::blue);
  update();
}

QPainterPath Symbol::painterPath(void)
{
  m_cachedPath = QPainterPath();
  m_bounding = QRectF();
  return m_cachedPath;
}

void Symbol::invalidate(void)
{
  m_valid = false;
}

void Symbol::addChild(Symbol* symbol)
{
  //symbol->setParentItem(this);
  addToGroup(symbol);
  m_symbols.append(symbol);
}
