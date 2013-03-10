#include "layer.h"

#include <QtGui>

#include "context.h"
#include "odbppgraphicsscene.h"

Layer::Layer(QString step, QString layer):
  GraphicsLayer(NULL), m_step(step), m_layer(layer), m_notes(NULL)
{
  GraphicsLayerScene* scene = new GraphicsLayerScene;
  m_features = new Features(step.toLower(),
      "steps/%1/layers/" + layer.toLower() +"/features");
  m_features->addToScene(scene);
  setLayerScene(scene);
}

Layer::~Layer()
{
  if (m_notes) {
    delete m_notes;
  }
  delete m_features;
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

void Layer::setHighlightEnabled(bool status)
{
  m_layerScene->setHighlightEnabled(status);
}

void Layer::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mousePressEvent(event);
}

void Layer::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mouseDoubleClickEvent(event);
}
