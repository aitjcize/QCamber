#ifndef __ODBPPGRAPHICSVIEW_H__
#define __ODBPPGRAPHICSVIEW_H__

#include <QGraphicsView>
#include "feature.h"
#include "profile.h"

#include "odbppgraphicsscene.h"

class ODBPPGraphicsView: public QGraphicsView {
  Q_OBJECT

public:
  typedef enum { AreaZoom = 0, MousePan } ZoomMode;

  ODBPPGraphicsView(QWidget* parent = 0);
  ~ODBPPGraphicsView();

  void setZoomMode(ZoomMode mode);
  void loadProfile(QString step);
  void setBackgroundColor(QColor color);

  void clearScene(void);
  void addItem(Symbol* symbol);
  void removeItem(Symbol* symbol);
  void zoomToProfile(void);

public slots:
  void zoomToRect(QRectF rect);

protected:
  void scaleView(qreal scaleFactor);
  virtual void wheelEvent(QWheelEvent* event);
  virtual void keyPressEvent(QKeyEvent* event);

private:
  ODBPPGraphicsScene* m_scene;
  ZoomMode m_zoomMode;
  Profile* m_profile;
};

#endif /* __ODBPPGRAPHICSVIEW_H__ */
