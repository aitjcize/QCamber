#ifndef __ODBPPGRAPHICSMINIMAPVIEW_H__
#define __ODBPPGRAPHICSMINIMAPVIEW_H__

#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "layer.h"
#include "odbppgraphicsscene.h"
#include "profile.h"

class ODBPPGraphicsMiniMapView: public QGraphicsView {
  Q_OBJECT

public:
  ODBPPGraphicsMiniMapView(QWidget* parent = 0);
  ~ODBPPGraphicsMiniMapView();

  void loadProfile(QString step);
  void setBackgroundColor(QColor color);

  void zoomToAll(void);
  void scaleView(qreal scaleFactor);

signals:
  void minimapRectSelected(QRectF rect);

public slots:
  void zoomToRect(QRectF rect);
  void zoomMainViewToRect(QRectF rect);

protected:
  virtual void keyPressEvent(QKeyEvent* event);

private:
  ODBPPGraphicsScene* m_scene;
  QGraphicsRectItem* m_rect;
  Profile* m_profile;
};

#endif /* __ODBPPGRAPHICSMINIMAPVIEW_H__ */
