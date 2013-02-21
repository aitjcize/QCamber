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

protected:
  void wheelEvent(QWheelEvent *event);
  void scaleView(qreal scaleFactor);

private:
  Profile* m_profile;
};

#endif /* __ODBPPGRAPHICSVIEW_H__ */
