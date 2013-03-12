#include "odbppgraphicsscene.h"

#include <QtGui>

#include "context.h"

ODBPPGraphicsScene::ODBPPGraphicsScene(QObject* parent):
  QGraphicsScene(parent), m_state(S_AREA_ZOOM), m_measured(false)
{
  m_rubberBand = new QGraphicsRectItem;
  m_measureRubberBand = new MeasureGraphicsItem;
  setBackgroundColor(ctx.bg_color);
}

ODBPPGraphicsScene::~ODBPPGraphicsScene()
{
  delete m_rubberBand;
  delete m_measureRubberBand;
}

void ODBPPGraphicsScene::setAreaZoomEnabled(bool status)
{
  if (m_measured) {
    removeItem(m_measureRubberBand);
    m_measured = false;
  }
  m_state = (status? S_AREA_ZOOM: S_NONE);
}

void ODBPPGraphicsScene::setMeasureEnabled(bool status)
{
  if (m_state == S_AREA_ZOOM_ACTIVE) {
    removeItem(m_rubberBand);
  }
  m_state = (status? S_MEASURE: S_NONE);
}

void ODBPPGraphicsScene::setHighlightEnabled(bool status)
{
  for (int i = 0; i < m_layers.size(); ++i) {
    dynamic_cast<GraphicsLayerScene*>(
        m_layers[i]->layerScene())->setHighlightEnabled(status);
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
  switch (m_state) {
  case S_AREA_ZOOM_ACTIVE:
    m_rubberBand->setRect(QRectF(m_rubberPS, event->scenePos()).normalized());
    break;
  case S_MEASURE_ACTIVE:
    QRectF rect = QRectF(m_rubberPS, event->scenePos()).normalized();
    m_measureRubberBand->setRect(rect);
    emit measureRectSelected(rect);
    break;
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
  switch (m_state) {
  case S_AREA_ZOOM:
    m_state = S_AREA_ZOOM_ACTIVE;
    m_rubberPS = event->scenePos();
    m_rubberBand->setRect(QRectF(m_rubberPS, m_rubberPS).normalized());
    addItem(m_rubberBand);
    break;
  case S_AREA_ZOOM_ACTIVE:
    m_state = S_AREA_ZOOM;
    removeItem(m_rubberBand);
    emit rectSelected(QRectF(m_rubberPS, event->scenePos()));
    break;
  case S_MEASURE:
    if (!m_measured) {
      addItem(m_measureRubberBand);
    }
    m_state = S_MEASURE_ACTIVE;
    m_measured = true;
    m_rubberPS = event->scenePos();
    m_measureRubberBand->setRect(QRectF(m_rubberPS, m_rubberPS).normalized());
    break;
  case S_MEASURE_ACTIVE:
    m_state = S_MEASURE;
    break;
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
    if (m_state == S_AREA_ZOOM_ACTIVE) {
      m_state = S_AREA_ZOOM;
      removeItem(m_rubberBand);
    }
    return;
  }
  QGraphicsScene::keyPressEvent(event);
}
