#include "layer.h"

#include <QtGui>

#include "context.h"

Layer::Layer(QString step, QString layer):
  QGraphicsItem(NULL), m_step(step), m_layer(layer), m_notes(NULL)
{
  m_features = new Features(ctx.loader->featuresPath(
        QString("steps/%1/layers/%2").arg(step).arg(layer))),

  m_scene = new QGraphicsScene;
  m_scene->addItem(m_features);
  m_view = new QGraphicsView;
  m_view->setScene(m_scene);
}

Layer::~Layer()
{
  if (m_notes) {
    delete m_notes;
  }
}

QString Layer::step()
{
  return m_step;
}

QString Layer::layer()
{
  return m_layer;
}

Notes* Layer::notes()
{
  if (!m_notes) {
    m_notes = new Notes(m_step, m_layer);
  }
  return m_notes;
}

void Layer::setViewRect(const QRect& rect)
{
  m_viewRect = rect;
}

void Layer::setSceneRect(const QRectF& rect)
{
  m_sceneRect = rect;
}

void Layer::setPen(const QPen& pen)
{
  m_features->setPen(pen);
}

void Layer::setBrush(const QBrush& brush)
{
  m_features->setBrush(brush);
}

QRectF Layer::boundingRect() const
{
  return m_scene->itemsBoundingRect();
}

void Layer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget)
{
  QPixmap pixmap(m_viewRect.size());
  QBitmap alphaMask(m_viewRect.size());
  alphaMask.clear();
  pixmap.setMask(alphaMask);

  QPainter sourcePainter(&pixmap);
  m_scene->render(&sourcePainter, m_viewRect, m_sceneRect);

  painter->setCompositionMode(QPainter::CompositionMode_Difference);
  painter->drawPixmap(m_sceneRect, pixmap, m_viewRect);
}

void Layer::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mousePressEvent(event);
}

void Layer::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mouseDoubleClickEvent(event);
}
