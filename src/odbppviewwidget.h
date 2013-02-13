#ifndef __ODBPP_VIEW_WIDGET_H__
#define __ODBPP_VIEW_WIDGET_H__

#include <QGraphicsView>
#include "feature.h"



class ODBPPViewWidget: public QGraphicsView {
  Q_OBJECT

public:
  ODBPPViewWidget(QWidget* parent = 0);
  Features* load_feature(QString filename,const QColor color = Qt::red,const QBrush brush = Qt::transparent);
  Features* load_profile(QString step);
  void clear_scene(){scene->clear();}
  QGraphicsScene *GetScene(){return scene;}

protected:
  void wheelEvent(QWheelEvent *event);
  void scaleView(qreal scaleFactor);

private:
  QGraphicsScene *scene;
};

#endif /* __ODBPP_VIEW_WIDGET_H__ */
