#include "odbppgraphicsscene.h"

#include <QtGui>

ODBPPGraphicsScene::ODBPPGraphicsScene(QObject* parent):
  QGraphicsScene(parent), m_areaZoomEnabled(false), m_highlight(false),
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

bool ODBPPGraphicsScene::highlight(void)
{
  return m_highlight;
}

void ODBPPGraphicsScene::setHighlight(bool status)
{
  m_highlight = status;

  if (!status) {
    clearHighlight();
  }
}

void ODBPPGraphicsScene::clearHighlight(void)
{
  for (int i = 0; i < m_selectedSymbols.size(); ++i) {
    m_selectedSymbols[i]->restoreColor();
  }
  m_selectedSymbols.clear();
}

void ODBPPGraphicsScene::updateSelection(Symbol* symbol)
{
  clearHighlight();
  m_selectedSymbols.append(symbol);
  emit featureSelected(symbol);
}

void ODBPPGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  if (m_areaZoomEnabled) {
    m_rubberBand->setRect(QRectF(m_rubberPS, event->scenePos()));
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
      m_rubberBand->setRect(QRectF(m_rubberPS, m_rubberPS));
      addItem(m_rubberBand);
    } else {
      m_rubberBandActivated = false;
      removeItem(m_rubberBand);
      emit rectSelected(QRectF(m_rubberPS, event->scenePos()));
    }
  }
  QGraphicsScene::mousePressEvent(event);
}

void ODBPPGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsScene::mouseReleaseEvent(event);
}
