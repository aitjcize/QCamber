#ifndef __LAYER_H__
#define __LAYER_H__

#include <QGraphicsScene>
#include <QGraphicsView>

#include "feature.h"
#include "notes.h"
#include "symbol.h"

class Layer: public QGraphicsItem {
public:
  Layer(QString step, QString layer);
  virtual ~Layer();

  QString step();
  QString layer();
  Notes* notes();

  void setViewRect(const QRect& rect);
  void setSceneRect(const QRectF& rect);
  virtual void setPen(const QPen& pen);
  virtual void setBrush(const QBrush& brush);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
  Features* m_features;
  QGraphicsScene* m_scene;
  QGraphicsView* m_view;
  QString m_step;
  QString m_layer;
  Notes* m_notes;
  QRect m_viewRect;
  QRectF m_sceneRect;
};

#endif /* __LAYER_H__ */
