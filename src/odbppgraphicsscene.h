#ifndef __ODBPPGRAPHICSSCENE_H__
#define __ODBPPGRAPHICSSCENE_H__

#include <QGraphicsScene>
#include <QPointF>

class ODBPPGraphicsScene: public QGraphicsScene {
  Q_OBJECT

public:
  ODBPPGraphicsScene(QObject* parent = 0);

signals:
  void mouseMove(QPointF pos);

protected:
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);
};

#endif /* __ODBPPGRAPHICSSCENE_H__ */
