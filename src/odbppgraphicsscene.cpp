#include "odbppgraphicsscene.h"

#include <QtGui>

#include "context.h"

ODBPPGraphicsScene::ODBPPGraphicsScene(QObject* parent):
  QGraphicsScene(parent), m_areaZoomEnabled(false),
  m_rubberBandActivated(false), m_viewScaleFactor(-1)
{
  m_rubberBand = new QGraphicsRectItem;
  setBackgroundColor(ctx.bg_color);
}

ODBPPGraphicsScene::~ODBPPGraphicsScene()
{
  delete m_rubberBand;
}

void ODBPPGraphicsScene::setAreaZoomEnabled(bool status)
{
  m_areaZoomEnabled = status;
}

void ODBPPGraphicsScene::setHighlight(bool status)
{
  for (int i = 0; i < m_layers.size(); ++i) {
    dynamic_cast<GraphicsLayerScene*>(
        m_layers[i]->layerScene())->setHighlight(status);
  }
}

void ODBPPGraphicsScene::clearHighlight(void)
{
  for (int i = 0; i < m_layers.size(); ++i) {
    dynamic_cast<GraphicsLayerScene*>(
        m_layers[i]->layerScene())->clearHighlight();
  }
}

void ODBPPGraphicsScene::setBackgroundColor(QColor color)
{
  setBackgroundBrush(color);
  QColor icolor(255 - color.red(), 255 - color.green(), 255 - color.blue());
  m_rubberBand->setPen(QPen(icolor, 0));
  icolor.setAlpha(64);
  m_rubberBand->setBrush(icolor);
}

QList<GraphicsLayer*> ODBPPGraphicsScene::layers(void)
{
  return m_layers;
}

void ODBPPGraphicsScene::addLayer(GraphicsLayer* layer)
{
  addItem(layer);
  m_layers.append(layer);

  connect(layer->layerScene(), SIGNAL(featureSelected(Symbol*)),
      this, SIGNAL(featureSelected(Symbol*)));
}

void ODBPPGraphicsScene::removeLayer(GraphicsLayer* layer)
{
  removeItem(layer);
  m_layers.removeOne(layer);
}

void ODBPPGraphicsScene::updateLayerViewport(QRect viewRect, QRectF sceneRect)
{
  for (int i = 0; i < m_layers.size(); ++i) {
    m_layers[i]->setViewRect(viewRect);
    m_layers[i]->setSceneRect(sceneRect);
  }
}

void ODBPPGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  if (m_areaZoomEnabled) {
    m_rubberBand->setRect(QRectF(m_rubberPS, event->scenePos()).normalized());
  }
  emit mouseMove(event->scenePos());
  QGraphicsScene::mouseMoveEvent(event);
}

void ODBPPGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsScene::mouseDoubleClickEvent(event);
}

void ODBPPGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  if (m_areaZoomEnabled) {
    if (!m_rubberBandActivated) {
      m_rubberPS = event->scenePos();
      m_rubberBandActivated = true;
      m_rubberBand->setRect(QRectF(m_rubberPS, m_rubberPS).normalized());
      addItem(m_rubberBand);
    } else {
      m_rubberBandActivated = false;
      removeItem(m_rubberBand);
      emit rectSelected(QRectF(m_rubberPS, event->scenePos()));
    }
  }

  for (int i = 0; i < m_layers.size(); ++i) {
    QApplication::sendEvent(m_layers[i]->layerScene(), event);
  }
  QGraphicsScene::mousePressEvent(event);
}

void ODBPPGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  for (int i = 0; i < m_layers.size(); ++i) {
    QApplication::sendEvent(m_layers[i]->layerScene(), event);
  }
  QGraphicsScene::mouseReleaseEvent(event);
}

void ODBPPGraphicsScene::keyPressEvent(QKeyEvent* event)
{
  switch (event->key()) {
  case Qt::Key_Escape:
    if (m_rubberBandActivated) {
      m_rubberBandActivated = false;
      removeItem(m_rubberBand);
    }
    return;
  }
  QGraphicsScene::keyPressEvent(event);
}
