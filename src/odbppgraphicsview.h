#ifndef __ODBPPGRAPHICSVIEW_H__
#define __ODBPPGRAPHICSVIEW_H__

#include <QGraphicsView>
#include "feature.h"
#include "profile.h"

#include "odbppgraphicsscene.h"

class ODBPPGraphicsView: public QGraphicsView {
  Q_OBJECT

public:
  ODBPPGraphicsView(QWidget* parent = 0);
  Features* loadFeature(QString filename, const QColor color = Qt::red,
      const QBrush brush = Qt::red);
  void loadProfile(QString step);
  void setBackgroundColor(QColor color);

  void clear_scene(){ scene()->clear(); }
  void addItem(Features *feat){ scene()->addItem(feat); }
  void removeItem(Features *feat){ scene()->removeItem(feat); }
  void zoomToProfile(void);

public slots:
  void zoomToRect(QRectF rect);

protected:
  void scaleView(qreal scaleFactor);
  virtual void wheelEvent(QWheelEvent *event);

private:
  Profile* m_profile;
};

#endif /* __ODBPPGRAPHICSVIEW_H__ */
