#include "odbppgraphicsscene.h"

#include <QtGui>

#include "symbol.h"

ODBPPGraphicsScene::ODBPPGraphicsScene(QObject* parent):
  QGraphicsScene(parent)
{
  
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
  }
}
