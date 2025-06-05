#include "componentsymbol.h"
#include <QtWidgets>
#include "graphicslayerscene.h"

ComponentSymbol::ComponentSymbol(const PackageDataStore::PackageInfo& info,
                                 const QString& designator)
  : Symbol("component"), m_pin1(0,0), m_designator(designator),
    m_designatorItem(NULL)
{
  // Component outlines are drawn without fill
  m_brush = Qt::NoBrush;
  m_path = info.bodyPath;
  for (const auto& pin : info.pins) {
    m_path.addPath(pin.path);
    if (pin.number == 1)
      m_pin1 = QPointF(pin.x, -pin.y);
  }
  m_bounding = m_path.boundingRect();
  if (m_bounding.isNull() && info.xmax > info.xmin && info.ymax > info.ymin)
    m_bounding = QRectF(info.xmin, -info.ymax,
                        info.xmax - info.xmin, info.ymax - info.ymin);

  m_designatorFont = QApplication::font();
  if (!m_designator.isEmpty()) {
    m_designatorItem = new QGraphicsSimpleTextItem(m_designator, this);
    m_designatorItem->setFont(m_designatorFont);
    m_designatorItem->setBrush(m_pen.color());

    QRectF br = m_designatorItem->boundingRect();
    qreal targetHeight = 0.02; // roughly the diameter of the pin one marker
    qreal scale = br.height() > 0 ? targetHeight / br.height() : 1.0;
    m_designatorItem->setScale(scale);

    QRectF textRect = QTransform::fromScale(scale, scale).mapRect(br);
    textRect.moveCenter(m_bounding.center());
    m_designatorItem->setPos(textRect.topLeft());
    m_bounding = m_bounding.united(textRect);
  }
}

QPainterPath ComponentSymbol::painterPath(void)
{
  return m_path;
}

void ComponentSymbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
    QWidget *widget)
{
  // Use base class rendering but always keep body outline only
  QBrush savedBrush = m_brush;
  m_brush = Qt::NoBrush;
  Symbol::paint(painter, option, widget);
  m_brush = savedBrush;

  painter->setPen(Qt::NoPen);
  painter->setBrush(QBrush(m_pen.color()));
  painter->drawEllipse(m_pin1, 0.01, 0.01);
  painter->setPen(m_pen);
  painter->setBrush(Qt::NoBrush);
}

void ComponentSymbol::setPen(const QPen& pen)
{
  Symbol::setPen(pen);
  if (m_designatorItem)
    m_designatorItem->setBrush(pen.color());
}

void ComponentSymbol::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  GraphicsLayerScene* s = dynamic_cast<GraphicsLayerScene*>(scene());

  if (!s || !s->highlight() || m_selected) {
    return;
  }

  m_selected = true;
  m_prevPen = m_pen;
  m_prevBrush = m_brush;

  setPen(QPen(Qt::blue, 0));
  setBrush(Qt::NoBrush);
  update();

  s->updateSelection(this);
}
