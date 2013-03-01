#include "odbppgraphicsscene.h"

#include <QtGui>

ODBPPGraphicsScene::ODBPPGraphicsScene(QObject* parent):
  QGraphicsScene(parent), m_areaZoomEnabled(false),
  m_rubberBandActivated(false), m_viewScaleFactor(-1)
{
  m_rubberBand = new QGraphicsRectItem;
  m_rubberBand->setBrush(Qt::transparent);
}

void ODBPPGraphicsScene::setAreaZoomEnabled(bool status)
{
  m_areaZoomEnabled = status;
}

void ODBPPGraphicsScene::setViewScaleFactor(qreal factor)
{
  if (m_viewScaleFactor < 0) {
    m_penWidth = 0.01 * factor;
    m_viewScaleFactor = 1;
  }
  m_penWidth /= factor;
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

void ODBPPGraphicsScene::addLayer(GraphicsLayer* layer)
{
  addItem(layer);
  m_layers.append(layer);

  connect(layer->layerScene(), SIGNAL(featureSelected(Symbol*)),
      this, SIGNAL(featureSelected(Symbol*)));
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
      m_rubberBand->setPen(QPen(Qt::white, m_penWidth));
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
