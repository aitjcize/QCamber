#ifndef __ODBPPGRAPHICSSCENE_H__
#define __ODBPPGRAPHICSSCENE_H__

#include <QGraphicsScene>
#include <QPointF>

#include "symbol.h"

class ODBPPGraphicsScene: public QGraphicsScene {
  Q_OBJECT

public:
  ODBPPGraphicsScene(QObject* parent = 0);
  void setAreaZoomEnabled(bool status);

signals:
  void mouseMove(QPointF);
  void featureSelected(Symbol*);
  void rectSelected(QRectF);

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);

private:
  QPointF m_rubberPS;
  QPointF m_rubberPE;
  bool m_areaZoomEnabled;
};

#endif /* __ODBPPGRAPHICSSCENE_H__ */
