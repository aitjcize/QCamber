#include "layer.h"

#include "context.h"

Layer::Layer(QString step, QString layer):
  Features(ctx.loader->featuresPath(
        QString("steps/%1/layers/%2").arg(step).arg(layer))),
  m_step(step), m_layer(layer), m_notes(NULL)
{
  m_layerEffect = new LayerGraphicsEffect();
  setGraphicsEffect(m_layerEffect);
}

Layer::~Layer()
{
  delete m_layerEffect;
  
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

void Layer::setOpacity(qreal opacity)
{
  m_layerEffect->setOpacity(opacity);
}

void Layer::setDoComposite(bool status)
{
  m_layerEffect->setDoComposite(status);
}

void Layer::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mousePressEvent(event);
}

void Layer::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mouseDoubleClickEvent(event);
}
