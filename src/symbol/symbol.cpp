#include "symbol.h"

#include <QDebug>

#include "context.h"
#include "odbppgraphicsscene.h"

Symbol::Symbol(QString name, QString pattern, Polarity polarity):
  m_name(name), m_pattern(pattern), m_pen(QPen(Qt::red, 0)), m_brush(Qt::red),
  m_polarity(polarity), m_valid(false), m_selected(false)
{
  setHandlesChildEvents(false);
  setFlags(ItemIsSelectable);
  //setCacheMode(DeviceCoordinateCache);
}

Symbol::~Symbol()
{
}

QString Symbol::name(void)
{
  return m_name;
}

QString Symbol::infoText(void)
{
  QString info = QString("X=%1, Y=%2, %3, %4") \
    .arg(pos().x()).arg(pos().y()) \
    .arg(m_name).arg((m_polarity == P)? "POS": "NEG");

  if (m_name != "surface") {
    info += QString(", Ang=%1").arg(rotation());
    if (transform().m11() == -1) {
      info += ", Mirror";
    }
  }
  return info;
}

QRectF Symbol::boundingRect() const
{
  if (m_symbols.count()) {
    return childrenBoundingRect();
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
  //QGraphicsItemGroup::paint(painter, option, widget);

  // Paint painterPath
  if (m_polarity == P) {
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
  } else {
    if (m_selected) {
      painter->setPen(m_pen);
      painter->setBrush(m_brush);
    } else {
      painter->setPen(QPen(ctx.bg_color, 0));
      painter->setBrush(ctx.bg_color);
    }
  }

  painterPath();
  painter->drawPath(m_cachedPath);
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
  symbol->setParentItem(this);
  //addToGroup(symbol);
  m_symbols.append(symbol);
}

void Symbol::restoreColor(void)
{
  m_selected = false;
  setPen(m_prevPen);
  setBrush(m_prevBrush);
  update();
}

void Symbol::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  ODBPPGraphicsScene* s = dynamic_cast<ODBPPGraphicsScene*>(scene());

  if (!s->highlight()) {
    return;
  }

  if (m_selected) {
    return;
  }

  m_selected = true;
  m_prevPen = m_pen;
  m_prevBrush = m_brush;

  setPen(QPen(Qt::blue, 0));
  setBrush(Qt::blue);
  update();

  s->updateSelection(this);
}

void Symbol::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
}
