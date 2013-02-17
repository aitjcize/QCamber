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
  QList<QGraphicsItem*> it = items(mouseEvent->scenePos());
  for (int i = 0; i < it.size(); ++i) {
    int idx = it.indexOf(it[i]->parentItem());
    if (idx != -1 && it[idx]->parentItem() != NULL) {
      tbr.append(it[i]);
      //qDebug() << "remove" << dynamic_cast<Symbol*>(it[i])->name();
    }
  }

  for (int i = 0; i < tbr.size(); ++i) {
    it.removeOne(tbr[i]);
  }
#define AREA(x) ((x)->boundingRect().width() * (x)->boundingRect().height())

  tbr.clear();
  QGraphicsItem* current = NULL;
  for (int i = 0; i < it.size(); ++i) {
    //qDebug() << "next" << dynamic_cast<Symbol*>(it[i])->name();
    if (current) {
      //qDebug() << current->boundingRect() << it[i]->boundingRect();
    }
    if (!current || AREA(current) > AREA(it[i])) {
      current = it[i];
    }
  }
  //qDebug() << dynamic_cast<Symbol*>(current)->name();
  sendEvent(current, mouseEvent);

  //QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}
