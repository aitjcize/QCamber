#ifndef __ODBPPGRAPHICSSCENE_H__
#define __ODBPPGRAPHICSSCENE_H__

#include <QGraphicsScene>

class ODBPPGraphicsScene: public QGraphicsScene {
public:
  ODBPPGraphicsScene(QObject* parent = 0);

protected:
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);
};

#endif /* __ODBPPGRAPHICSSCENE_H__ */
