#include "odbppgraphicsscene.h"

#include <QtGui>

ODBPPGraphicsScene::ODBPPGraphicsScene(QObject* parent):
  QGraphicsScene(parent), m_areaZoomEnabled(false)
{
}

void ODBPPGraphicsScene::setAreaZoomEnabled(bool status)
{
  m_areaZoomEnabled = status;
}

void ODBPPGraphicsScene::updateSelection(Symbol* symbol)
{
  for (int i = 0; i < m_selectedSymbols.size(); ++i) {
    m_selectedSymbols[i]->restoreColor();
  }
  m_selectedSymbols.clear();
  m_selectedSymbols.append(symbol);
  emit featureSelected(symbol);
}

void ODBPPGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
  emit mouseMove(mouseEvent->scenePos());
  QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void ODBPPGraphicsScene::mouseDoubleClickEvent(
    QGraphicsSceneMouseEvent* mouseEvent)
{
  QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void ODBPPGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  if (m_areaZoomEnabled) {
    m_rubberPS = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
  }
  QGraphicsScene::mousePressEvent(event);
}

void ODBPPGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  if (m_areaZoomEnabled) {
    m_rubberPE = event->scenePos();
    if (m_rubberPS != m_rubberPE) {
      emit rectSelected(QRectF(m_rubberPS, m_rubberPE));
    }
  }
  QGraphicsScene::mouseReleaseEvent(event);
}
