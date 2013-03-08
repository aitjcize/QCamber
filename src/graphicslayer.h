#ifndef __GRAPHICSLAYER_H__
#define __GRAPHICSLAYER_H__

#include <QGraphicsScene>

#include "feature.h"
#include "graphicslayerscene.h"
#include "notes.h"
#include "symbol.h"

class GraphicsLayer: public QGraphicsItem {
public:
  GraphicsLayer(QGraphicsItem* parent = 0);
  virtual ~GraphicsLayer();

  void setLayerScene(GraphicsLayerScene* scene);
  QGraphicsScene* layerScene(void);

  void setViewRect(const QRect& rect);
  void setSceneRect(const QRectF& rect);
  void setShowOutline(bool status);
  virtual void setPen(const QPen& pen);
  virtual void setBrush(const QBrush& brush);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);

  void forceUpdate(void);

protected:
  GraphicsLayerScene* m_layerScene; QRect m_viewRect;
  QRectF m_sceneRect;
  QPixmap m_pixmap;
  QRectF m_prevSceneRect;
  QPen m_pen;
  QBrush m_brush;
  bool m_showOutline;
};

#endif /* __GRAPHICSLAYER_H__ */
