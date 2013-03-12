#ifndef __ODBPPGRAPHICSSCENE_H__
#define __ODBPPGRAPHICSSCENE_H__

#include <QGraphicsScene>
#include <QPointF>

#include "graphicslayer.h"
#include "measuregraphicsitem.h"
#include "symbol.h"

class ODBPPGraphicsScene: public QGraphicsScene {
  Q_OBJECT

public:
  typedef enum {
    S_NONE,
    S_AREA_ZOOM,
    S_AREA_ZOOM_ACTIVE,
    S_MEASURE,
    S_MEASURE_ACTIVE
  } State;

  ODBPPGraphicsScene(QObject* parent = 0);
  ~ODBPPGraphicsScene();

  void setAreaZoomEnabled(bool status);

  QList<GraphicsLayer*> layers(void);
  void addLayer(GraphicsLayer* layer);
  void removeLayer(GraphicsLayer* layer);
  void updateLayerViewport(QRect viewRect, QRectF sceneRect);

  void setMeasureEnabled(bool status);
  void setHighlightEnabled(bool status);
  void clearHighlight(void);

signals:
  void mouseMove(QPointF);
  void featureSelected(Symbol*);
  void rectSelected(QRectF);
  void measureRectSelected(QRectF);

public slots:
  void setBackgroundColor(QColor color);

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
  virtual void keyPressEvent(QKeyEvent* event);

private:
  State m_state;
  QGraphicsRectItem* m_rubberBand;
  MeasureGraphicsItem* m_measureRubberBand;
  QPointF m_rubberPS;
  QColor m_reubberBandColor;
  bool m_measured;
  QList<GraphicsLayer*> m_layers;
};

#endif /* __ODBPPGRAPHICSSCENE_H__ */
