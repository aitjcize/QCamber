#ifndef __ODBPPGRAPHICSVIEW_H__
#define __ODBPPGRAPHICSVIEW_H__

#include <QGraphicsView>
#include "graphicslayer.h"
#include "profile.h"

#include "odbppgraphicsscene.h"

class ODBPPGraphicsView: public QGraphicsView {
  Q_OBJECT

public:
  typedef enum { None = 0, AreaZoom, MousePan } ZoomMode;

  ODBPPGraphicsView(QWidget* parent = 0);
  ~ODBPPGraphicsView();

  void setZoomMode(ZoomMode mode);
  void loadProfile(QString step);
  void setMeasureEnabled(bool status);
  void setHighlightEnabled(bool status);
  void clearHighlight(void);

  void clearScene(void);
  void addLayer(GraphicsLayer* layer);
  void removeLayer(GraphicsLayer* layer);
  void addItem(QGraphicsItem* item, bool scale_invariant=false);
  void removeItem(QGraphicsItem* item);

  void initialZoom(void);
  void zoomToAll(void);
  void scaleView(qreal scaleFactor);
  void scrollView(int dx, int dy);

signals:
  void sceneRectChanged(QRectF);

public slots:
  void zoomToRect(QRectF rect);
  void updateLayerViewport(void);
  void setBackgroundColor(QColor color);

protected:
  virtual void wheelEvent(QWheelEvent* event);
  virtual void keyPressEvent(QKeyEvent* event);
  virtual void resizeEvent(QResizeEvent* event);

private:
  ODBPPGraphicsScene* m_scene;
  ZoomMode m_zoomMode;
  Profile* m_profile;
  Symbol* m_origin;
  QList<QGraphicsItem*> m_scaleInvariantItems;
};

#endif /* __ODBPPGRAPHICSVIEW_H__ */
