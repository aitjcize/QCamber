#ifndef __ODBPP_VIEW_WIDGET_H__
#define __ODBPP_VIEW_WIDGET_H__

#include <QGraphicsView>
#include "feature.h"
#include "profile.h"

class ODBPPViewWidget: public QGraphicsView {
  Q_OBJECT

public:
  ODBPPViewWidget(QWidget* parent = 0);
  Features* loadFeature(QString filename, const QColor color = Qt::red,
      const QBrush brush = Qt::red);
  Profile* loadProfile(QString step);
  void clear_scene(){scene->clear();}
  QGraphicsScene *GetScene(){return scene;}
  void addItem(Features *bot){scene->addItem(bot);}
  void removeItem(Features *bot){scene->removeItem(bot);}

protected:
  void wheelEvent(QWheelEvent *event);
  void scaleView(qreal scaleFactor);

private:
  QGraphicsScene *scene;
};

#endif /* __ODBPP_VIEW_WIDGET_H__ */
