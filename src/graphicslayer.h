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

  virtual void setPen(const QPen& pen);
  virtual void setBrush(const QBrush& brush);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);

private:
  GraphicsLayerScene* m_layerScene;
  QRect m_viewRect;
  QRectF m_sceneRect;
};

#endif /* __GRAPHICSLAYER_H__ */
