#include "odbppgraphicsscene.h"

#include <QtGui>

ODBPPGraphicsScene::ODBPPGraphicsScene(QObject* parent):
  QGraphicsScene(parent)
{
  
}

void ODBPPGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
  emit mouseMove(mouseEvent->scenePos());
}

void ODBPPGraphicsScene::mouseDoubleClickEvent(
    QGraphicsSceneMouseEvent* mouseEvent)
{
  QList<QGraphicsItem*> tbr;
  QList<QGraphicsItem*> it = items(mouseEvent->scenePos(),
      Qt::ContainsItemShape, Qt::DescendingOrder);

  /*
  for (int i = 0; i < it.size(); ++i) {
    qDebug() << dynamic_cast<Symbol*>(it[i])->name() << it[i];
  }
  */

  QGraphicsItem* top = it.at(0);
  if (top->parentItem() != NULL && top->parentItem()->parentItem() != NULL) {
    top = top->parentItem();
  }

  if (top->parentItem() != NULL) {
    sendEvent(top, mouseEvent);
    emit featureSelected(dynamic_cast<Symbol*>(top));
  }
}

void ODBPPGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  m_rubberPS = event->scenePos();
  QGraphicsScene::mousePressEvent(event);
}

void ODBPPGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  m_rubberPE = event->scenePos();
  if (m_rubberPS != m_rubberPE) {
    emit rectSelected(QRectF(m_rubberPS, m_rubberPE));
  }
}
